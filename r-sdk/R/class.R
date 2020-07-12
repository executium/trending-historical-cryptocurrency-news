#' ApiAccess
#'
#' /**
#'* @param string api_key       Your API key obtained from executium.com
#'* @param string api_secret    Your API secret obtained from executium.com
#'*/
#' ApiAccess class
#'
#' @export
ApiAccess <- R6::R6Class(
  "ApiAccess",


  public = list(

    initialize = function(api_key, api_secret, api_version = 'v1') {
      if(requireNamespace("RCurl", quietly = TRUE)) {
        private$api_key = api_key
        private$api_secret = api_secret
      } else {
        stop('Fatal Error; CURL for R is not installed')
      }
    },

    version = 2,
    domain = 'https://trendingnews.executium.com',
    useragent = 'API v2',
    path = '',
    url = '',
    endpoints_list = list(),
    timeout = 3000,
    payload = list(),

    config = function(arr) {
      purrr::iwalk(arr, ~{
        self[[.y]] <- .x
      })
    },

    get_api_url = function(path) {
      paste0(self$domain, '/api/v', self$version, '/', path)
    },

    set_path = function(path) {
      self$path <- path
    },

    get_config = function() {
      list(
        version = self$version,
        domain = self$domain,
        useragent = self$useragent,
        path = self$path,
        url = self$url,
        endpoints_list = self$endpoints_list,
        timeout = self$timeout
      )
    },

    endpoints = function(input = list()) {

      if(length(input) == 0) {
        rtrn = self$endpoints_list
      } else {
        self$set_path('system/ep')
        rtrn = self$post(input, list())
        self$endpoints_list <- rtrn['returned']['data']
      }

      rtrn
    },

    send = function(path, input, payload) {
      self$set_path(path)
      rtrn <- self$post(input, payload)

      rtrn
    },

    nonce = function() {
      round(as.numeric(lubridate::now()) * 10000000, 0)
    },

    auth = function() {
      self$payload['nonce'] <- format(self$nonce(), scientific = FALSE)

      b01 = str_replace_symbols(RCurl::base64Encode('{"typ":"JWT","alg":"HS256"}')[1])
      b02 = str_replace_symbols(RCurl::base64Encode(gsub('\\[\\"|\\"\\]', '', jsonlite::toJSON(self$payload)))[1])
      sig = digest::hmac(object = paste0(b01, ".", b02), key = private$api_secret, raw = TRUE, algo = 'sha256', serialize = FALSE)
      b03 = str_replace_symbols(RCurl::base64Encode(sig)[1])

      paste(b01, b02, b03, sep = '.')
    },

    post = function(input, payload) {
      self$payload = payload
      self$url = paste0(self$domain, '/api/v', self$version, '/', self$path)

      library(curl)

      handle2 <- curl::new_handle()

      curl::handle_setopt(handle2, header = 0L)
      curl::handle_setopt(handle2, noprogress = 1L)
      curl::handle_setopt(handle2, timeout_ms = 3000L)
      curl::handle_setopt(handle2, followlocation = 1L)
      curl::handle_setopt(handle2, useragent = "API v2")
      curl::handle_setopt(handle2, accept_encoding = "json")
      curl::handle_setopt(handle2, httpheader = c(
        sprintf('Key: %s', private$api_key),
        sprintf('Authorization: %s', self$auth()))
      )


      ##/
      if(length(input)>0) {
        curl::handle_setopt(handle2, post = 1L)
        curl::handle_setopt(handle2, postfields = httr:::compose_query(input))
      }

      ##/

      ch <- curl::curl_fetch_memory(url = "https://trendingnews.executium.com/api/v2/public/trending-news-data", handle = handle2)
      out = list('success' = FALSE, 'returned' = list(), 'network_info' = list())
      rtrn = TRUE

      if(is.null(rtrn)) {
        out[['success']] = FALSE
        out[['returned']] = jsonlite::fromJSON(rawToChar(ch$content))
        out[['network_info']] = curl_getinfo(ch)
      } else {
        out[['success']] = TRUE
        out[['returned']] = jsonlite::fromJSON(rawToChar(ch$content))
        out[['network_info']] = curl_getinfo(ch)
      }

      out
    },


    get_endpoints = function() {
      self$endpoints_list
    },

    decode = function(result) {
      jsonlite::fromJSON(result, simplifyVector = TRUE)
    }
  ),

  private = list(
    api_key = '',
    api_secret = ''
  )
)
