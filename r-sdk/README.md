# Executium Trending News - R Programming Language
The `tests/` folder provides `valid` and `invalid` inputs so that you can experience all outputs. This SDK is provided as a starting point for anyone who is developing with `R`. You can thumb through and find the files which matter the most to to your development and in connecting with executiums trending news.

## Installation

1) Install `r-base`
```
sudo apt-get install r-base r-base-dev
```
2) 
```
Rscript /path/to/script.R
```
Optional, but not required for access to the free tier of trending news is the config files
```r
key = "your key here"
secret = "your secret here"
```
3) You need to install R packages, as follows:
```
Rscript -e 'install.packages("remotes")'
```
Optional, for test purposes
```
Rscript -e 'install.packages("testthat")'
```

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

The primary focus should be the following lines
```r
# Declare endpoint
endpoint ='public/trending-news-data'

# Parameters required (These are sent as POST)
input = list()
input['date'] = '2020-07-10'

# R list output
result = obj$send(endpoint, input, list())

```

The `endpoint` var is interchangable. Please consult the documentation for more information regarding available endpoints.

