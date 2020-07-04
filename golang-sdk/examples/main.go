package main

import (
	"fmt"
	"trending-historical-cryptocurrency-news/golang-sdk/examples/src"
)

func main() {
	obj := src.New(key, secret)
  
/*
  # Interchange the endpoint and consult the `REST-API` documentation for the required parameters
*/

	endpoint := "public/trending-news-data"

	payload := make(map[string]interface{})
	payload["date"] = '2020-07-04'

	result, err := obj.Send(endpoint, payload, map[string]interface{}{})
	if err != nil {
		fmt.Println(err)
	}

	fmt.Printf("%#v\n", result)
}
