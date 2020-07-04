package src

import (
	"crypto/hmac"
	"crypto/sha256"
	"encoding/base64"
	"encoding/json"
	"fmt"
	"net/http"
	"net/url"
	"strconv"
	"strings"
	"time"
)


// APIAccess is interface that states which methods need to be implemented
type APIAccess interface {
	Config(arr map[string]interface{})
	GetAPIURL(path string) string
	SetPath(path string)
	GetConfig() APIAccessStruct
	SetEndpoints(input []string)
	Send(path, input, payload string) map[string]interface{}
	Nonce() string
	Auth() string
	Post(input, payload string) map[string]interface{}
	GetEndpoints() []string
	Decode(result json.RawMessage) map[string]interface{}
}

// APIAccessStruct is the object that will be implementing APIAcess interface
type APIAccessStruct struct {
	apiKey    string
	apiSecret string
	Version   int
	Domain    string
	UserAgent string
	Path      string
	URL       string
	Endpoints []string
	Timeout   int64
	payload   map[string]interface{}
}

// PostResponse contains data returned from POST request
type PostResponse struct {
	Success  bool
	Returned map[string]interface{}
}

// New is used as a constructor for APIAccessStruct, use it to create new APIAcess objects
func New(apiKey, apiSecret string) (apiAccessStruct *APIAccessStruct) {
	apiAccessStruct = &APIAccessStruct{}

	apiAccessStruct.apiKey = apiKey
	apiAccessStruct.apiSecret = apiSecret
	apiAccessStruct.Version = 2
	apiAccessStruct.Domain = "https://trendingnews.executium.com"
	apiAccessStruct.UserAgent = "Executium Trending News (golang) API v2"
	apiAccessStruct.Timeout = 3000

	return apiAccessStruct
}

// Config is a ApiAccessStruct implementation of APIAccess interface function Config
// It receives a map of key-value pairs with which APIAccessStruct can be initialized
func (apiAccessStruct *APIAccessStruct) Config(arr map[string]interface{}) {
	for i, v := range arr {
		switch i {
		case "version":
			apiAccessStruct.Version = v.(int)
		case "domain":
			apiAccessStruct.Domain = v.(string)
		case "useragent":
			apiAccessStruct.UserAgent = v.(string)
		case "path":
			apiAccessStruct.Path = v.(string)
		case "url":
			apiAccessStruct.URL = v.(string)
		case "endpoints":
			apiAccessStruct.Endpoints = v.([]string)
		case "timeout":
			apiAccessStruct.Timeout = v.(int64)

		}
	}
}

// GetAPIURL is a APIAccessStruct implementation of APIAccess interface function GetAPIURL
// It returns full API URL by concatenating domain name with api version and path
func (apiAccessStruct *APIAccessStruct) GetAPIURL(path string) string {
	return apiAccessStruct.Domain + "/api/v" + strconv.Itoa(apiAccessStruct.Version) + "/" + path
}

// SetPath is a APIAccessStruct implementation of APIAccess interface function SetPath
// It sets the path inside the struct to the one that is passed as argument
func (apiAccessStruct *APIAccessStruct) SetPath(path string) {
	apiAccessStruct.Path = path
}

// GetConfig is a APIAccessStruct implementation of APIAccess interface function GetConfig
// It returns configuration set up inside APIAccessStruct
func (apiAccessStruct *APIAccessStruct) GetConfig() APIAccessStruct {
	return *apiAccessStruct
}

// SetEndpoints is a APIAccessStruct implementation of APIAccess interface function SetEndpoints
// It is used to set endpoints of the APIAccessStruct to response received from calling POST with given input
func (apiAccessStruct *APIAccessStruct) SetEndpoints(input map[string]interface{}) error {
	apiAccessStruct.SetPath("system/ep")
	ret, err := apiAccessStruct.Post(input, map[string]interface{}{})
	if err != nil {
		return err
	}

	apiAccessStruct.Endpoints = ret.Returned["data"].([]string)

	return nil
}

// Send is a APIAccessStruct implementation of APIAccess interface function Send
// It sets the path for API call and executes the POST request to API
func (apiAccessStruct *APIAccessStruct) Send(path string, input, payload map[string]interface{}) (*PostResponse, error) {
	apiAccessStruct.SetPath(path)
	return apiAccessStruct.Post(input, payload)
}

// Nonce is a APIAccessStruct implementation of APIAccess interface function Nonce
// It creates a nonce like given in requirements
func (apiAccessStruct *APIAccessStruct) Nonce() string {
	timeFormat := time.Now().UnixNano()
	return fmt.Sprintf("%v", timeFormat)[:18]
}

// Auth is a APIAccessStruct implementation of APIAccess interface function Auth
// It creates an authorization token passed to the API
func (apiAccessStruct *APIAccessStruct) Auth() (string, error) {
	apiAccessStruct.payload["nonce"] = apiAccessStruct.Nonce()

	// characters to be replaced and their replacements are listed one after another
	// since replacement is the same for all of b01, b02 and b03 same replacer is used
	replacer := strings.NewReplacer("+", "-", "/", "_", "=", "")

	b01 := replacer.Replace(base64.StdEncoding.EncodeToString([]byte(`{"typ":"JWT","alg":"HS256"}`)))

	// json marshalling (encoding into a string)
	encodedPayload, err := json.Marshal(apiAccessStruct.payload)
	if err != nil {
		return "", err
	}

	b02 := replacer.Replace(base64.StdEncoding.EncodeToString(encodedPayload))

	h := hmac.New(sha256.New, []byte(apiAccessStruct.apiSecret))
	h.Write([]byte(b01 + "." + b02))
	b03 := replacer.Replace(base64.StdEncoding.EncodeToString(h.Sum(nil)))
	return b01 + "." + b02 + "." + b03, nil

}

// Post is a APIAccessStruct implementation of APIAccess interface function Post
// It executes a Post request
func (apiAccessStruct *APIAccessStruct) Post(input, payload map[string]interface{}) (*PostResponse, error) {
	apiAccessStruct.payload = payload
	apiAccessStruct.URL = apiAccessStruct.Domain + "/api/v" + strconv.Itoa(apiAccessStruct.Version) + "/" + apiAccessStruct.Path

	// by default method is GET, if there is input passed as argument method becomes POST
	httpMethod := "GET"
	if len(input) > 0 {
		httpMethod = "POST"
	}

	// Add key value pairs to url encode
	data := url.Values{}
	for key, v := range input {
		value := fmt.Sprintf("%v", v)
		data.Set(key, value)
	}

	// API client with initialized timeout
	client := http.Client{
		Timeout: time.Duration(apiAccessStruct.Timeout) * time.Millisecond,
	}

	// request that the client will execute (with method, URL and body)
	req, err := http.NewRequest(httpMethod, apiAccessStruct.URL, strings.NewReader(data.Encode()))
	if err != nil {
		return nil, err
	}

	// Adding key header
	req.Header.Set("Key", apiAccessStruct.apiKey)

	auth, err := apiAccessStruct.Auth()
	if err != nil {
		return nil, err
	}

	// adding auth header
	req.Header.Set("Authorization", auth)
	// adding content-type header which is set by default with cURL
	req.Header.Add("Content-Type", "application/x-www-form-urlencoded")
	// adding user agent header
	req.Header.Set("User-Agent", apiAccessStruct.UserAgent)

	// client executes the request
	resp, err := client.Do(req)
	if err != nil {
		return nil, err
	}
	defer resp.Body.Close()

	// decode the response
	unmarshalMap := make(map[string]interface{})
	err = json.NewDecoder(resp.Body).Decode(&unmarshalMap)
	if err != nil {
		return nil, err
	}

	// add response to the object
	out := &PostResponse{}

	if unmarshalMap == nil {
		out.Success = false
		out.Returned = unmarshalMap
	} else {
		out.Success = true
		out.Returned = unmarshalMap
	}

	return out, nil

}

// GetEndpoints is a APIAccessStruct implementation of APIAccess interface function GetEndpoints
// It returns list of endpoints inside the APIAccessStruct object
func (apiAccessStruct *APIAccessStruct) GetEndpoints() []string {
	return apiAccessStruct.Endpoints
}

// Decode is a APIAccessStruct implementation of APIAccess interface function Decode
// It decodes bytes passed as arguments
func (apiAccessStruct *APIAccessStruct) Decode(result json.RawMessage) (map[string]interface{}, error) {
	unmarshalMap := make(map[string]interface{})
	err := json.Unmarshal(result, &unmarshalMap)
	if err != nil {
		return nil, err
	}

	return unmarshalMap, nil
}
