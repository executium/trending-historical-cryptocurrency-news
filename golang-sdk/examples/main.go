package main

import (
	"fmt"
	"trending-historical-cryptocurrency-news/golang-sdk/examples/src"
)

func main() {
	obj := src.New(key, secret)
  
/*
  # Interchange the endpoint and consult the `REST-API` documentation for the required `input`. `input` is the POST parameters which are required or optional.
*/
	endpoint := "public/trending-news-data"
	input := make(map[string]interface{})
	input["date"] = "2020-07-04"

	result, err := obj.Send(endpoint, input, map[string]interface{}{})
	if err != nil {
		fmt.Println(err)
	}

	fmt.Printf("%#v\n", result)
}
