using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Net.Http.Headers;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Security.Cryptography;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.Net;
using System.IO;
using System.Collections.Specialized;

namespace CSharpExample
{
    public class ApiAccess
    {

        #region Private properties

        private string _apiKey;
        private string _apiSecret;

        #endregion


        #region Public Properties

        public int Version { get; set; } = 2;
        public string Domain { get; set; } = "https://trendingnews.executium.com";
        public string UserAgent { get; set; } = "API v2 (C#)";
        public string Path { get; set; }
        public string Url { get; set; }
        public List<string> Endpoints { get; set; }
        public int Timeout { get; set; } = 10000;

        #endregion


        #region Constructor

        public ApiAccess(string apiKey, string apiSecret, string apiVersion = "v1")
        {
            _apiKey = apiKey;
            _apiSecret = apiSecret;
        }

        #endregion

        #region Methods


        /// <summary>
        /// Get absolute URL with version and Path included
        /// </summary>
        /// <param name="path">Endpoint path</param>
        /// <returns>Absolute URL</returns>
        public string GetApiUrl(string path) => $"{Domain}/api/v{Version}/{path}";

        /// <summary>
        /// Set Path that is used for URL construction, without version.
        /// </summary>
        /// <param name="path">Endpoint path</param>
        public void SetPath(string path) => Path = path;

        /// <summary>
        /// Get and Set endpoints from the API
        /// </summary>
        /// <param name="input">Formdata input for POST</param>
        public async void SetEndpoints(Dictionary<string, string> input)
        {
            SetPath("system/ep");
            var result = await Post(input, new List<string>());
            dynamic resultJson = JObject.Parse(result);
            Endpoints = resultJson;
            return;
        }

        /// <summary>
        /// Send POST request to the endpoint specified by path
        /// </summary>
        /// <param name="path">Endpoint path</param>
        /// <param name="input">Formdata input for POST</param>
        /// <param name="payload">Payload</param>
        /// <returns>Response</returns>
        public async Task<string> Send(string path, IDictionary<string, string> input, List<string> payload)
        {
            SetPath(path);
            return await Post(input, payload);
        }

        /// <summary>
        /// Get offset in miliseconds
        /// </summary>
        /// <returns>offset</returns>
        public string Nonce() => DateTime.UtcNow.Subtract(new DateTime(1970, 1, 1, 0, 0, 0)).Ticks.ToString();

        /// <summary>
        /// Construct Authroization token
        /// </summary>
        /// <returns>Authorization token</returns>
        public string Auth()
        {

            var bo1 = Base64Encode("{\"typ\":\"JWT\",\"alg\":\"HS256\"}")
                        .Replace('+', '-').Replace('/', '_').Replace("=", string.Empty);

            var bo2 = Base64Encode(JsonConvert.SerializeObject(new{nonce = Nonce()}))
                        .Replace('+', '-').Replace('/', '_').Replace("=", string.Empty);

            var bo3 = Base64Encode(HmacSHA256($"{bo1}.{bo2}", _apiSecret))
                        .Replace('+', '-').Replace('/', '_').Replace("=", string.Empty);

            return $"{bo1}.{bo2}.{bo3}";
        }


        /// <summary>
        /// Send POST request - first you need to specify path
        /// </summary>
        /// <param name="input">Formdata input for POST</param>
        /// <param name="payload">Payload</param>
        /// <returns>Response</returns>
        public async Task<string> Post(IDictionary<string, string> input, List<string> payload)
        {
            Url = $"{Domain}/api/v{Version}/{Path}";

            using (var client = new HttpClient())
            {
                client.DefaultRequestHeaders.Add("key", _apiKey);
                client.DefaultRequestHeaders.Add("authorization", Auth());
                client.DefaultRequestHeaders.Add("user-agent", "API V2");
                client.Timeout = TimeSpan.FromMilliseconds(Timeout);
                client.DefaultRequestHeaders.Accept.Add(new MediaTypeWithQualityHeaderValue("application/x-www-form-urlencoded"));
                if (input.Count() > 0)
                {
                    var content = new FormUrlEncodedContent(input);
                    var result = await client.PostAsync(Url, content);
                    var response = await result.Content.ReadAsStringAsync();
                    return response;
                }
            }

            return "";
        }

        /// <summary>
        /// Get Endpoints list
        /// </summary>
        /// <returns>Endpoints</returns>
        public List<string> GetEndpoints() => Endpoints;

        #endregion


        #region Added helper methods

        /// <summary>
        /// Encode String to Base64 string
        /// </summary>
        /// <param name="data">String to be encoded</param>
        /// <returns>Encoded string</returns>
        public string Base64Encode(string data)
        {
            byte[] binary = Encoding.Default.GetBytes(data);
            return Base64Encode(binary);
        }

        /// <summary>
        /// Encode Bytes to Base64 string
        /// </summary>
        /// <param name="data">Bytes to be encoded</param>
        /// <returns>Encoded string</returns>
        public string Base64Encode(byte[] data) => Convert.ToBase64String(data);


        /// <summary>
        /// Encript payload with HMAC SHA256 Algorythm
        /// </summary>
        /// <param name="data">Value to encript</param>
        /// <param name="key">Key used encript</param>
        /// <returns>Encrypted bytes</returns>
        static byte[] HmacSHA256(String data, String key)
        {
            using (HMACSHA256 hmac = new HMACSHA256(Encoding.ASCII.GetBytes(key)))
            {
                return hmac.ComputeHash(Encoding.ASCII.GetBytes(data));
            }
        }

        #endregion

    }
}
