library(executiumtrendingnews)
library(testthat)

## Load $key and $secret
source(system.file("examples/config.R", package = "executiumtrendingnews"))

## Create instance
obj <- ApiAccess$new(api_key = key, api_secret = secret)

test_that("ApiAccess instantiation works", {
  expect_equal(class(obj), c("ApiAccess", "R6"))
})

context("ApiAccess methods")

test_that("get_api_url works", {
  expect_equal(obj$get_api_url("test"), "https://trendingnews.executium.com/api/v2/test")
  expect_equal(obj$get_api_url(""), "https://trendingnews.executium.com/api/v2/")
})

test_that("set_path works", {
  # in place
  obj$set_path("test")

  expect_equal(obj$path, "test")
})

test_that("get_config works", {
  expect_equal(class(obj$get_config()), "list")
})

test_that("config works", {
  old_config <- obj$get_config()
  new_config <- list(
    version = 3,
    domain = 'https://trendingnews.executium.com/OKCONFIG',
    useragent = 'API v2/OKCONFIG',
    path = 'OKCONFIG',
    url = 'OKCONFIG',
    endpoints_list = list("OKCONFIG_1", "OKCONFIG_2"),
    timeout = 4000
  )
  obj$config(new_config)
  expect_equal(obj$get_config(), new_config)

  obj$config(old_config)
  expect_equal(obj$get_config(), old_config)
})

test_that("auth works", {
  expect_equal(class(obj$auth()), "character")
  expect_equal(length(obj$auth()), 1)
  expect_equal(names(obj$payload), "nonce")
})

test_that("send works", {

  # Declare endpoint
  endpoint ='public/trending-news-data'

  # Parameters required (These are sent as POST)
  input = list()
  input['date'] = '2020-07-10'

  result = obj$send(endpoint, input, list())
  expect_equal(class(result), "list")

  # jsonlite::toJSON(result, pretty = TRUE)
})

test_that("endpoints works", {
  obj$endpoints()
  expect_equal(obj$endpoints(), list())

  result = obj$endpoints(input = list(a = 1))
  jsonlite::toJSON(result, pretty = TRUE)
})




