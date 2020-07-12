# Executium Trending News - R Programming Language
The `tests/` folder provides `valid` and `invalid` inputs so that you can experience all outputs. 

## Example R script

```r
library(executiumtrendingnews)
library(jsonlite)

## Load key and secret
source(system.file("examples/config.R", package = "executiumtrendingnews"))

## Create instance
obj <- ApiAccess$new(api_key = key, api_secret = secret)

# Declare endpoint
endpoint ='public/trending-news-data'

# Parameters required (These are sent as POST)
input = list()
input['date'] = '2020-07-10'

# R list output
result = obj$send(endpoint, input, list())

```
