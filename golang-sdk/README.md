# Go-lang Scripts for Cryptocurrency Trending News

1. Navigate to `trending-historical-cryptocurrency-news/golang-sdk/examples` folder
2. Run `go install`
3. Executable will show up in the `bin` folder of `GOPATH`

### Interchanging `endpoints`
Please consult the [README](../README.md) for information regarding the `endpoints`. In the `examples/main.go` file you are provided the following are which you should modify:

```go

endpoint := "public/trending-public-news"
input := make(map[string]interface{})
input["date"] = "2020-07-04"

```

Beyond the above section of code, you do not need to modify any other code for simple working reasons.

For example, if you wanted to get the endpoint `public/trending-news-statistics` you would make the `main()` function as follows:

```go

func main() {
        obj := src.New(key, secret)
        endpoint := "public/trending-news-statistics"

        input := make(map[string]interface{})

        result, err := obj.Send(endpoint, input, map[string]interface{}{})
        if err != nil {
                fmt.Println(err)
        }

        fmt.Printf("%#v\n", result)
}   

```
As you can see, the input is declared but no additional input is required.

### Nonce
A special mention regarding the `nonce`. The `nonce` must be between 17 to 20 characters in length. The prefix is the current `unix timestamp`. If you are to modify the `interface` in `src` then please beaware that an expected format is expected.
