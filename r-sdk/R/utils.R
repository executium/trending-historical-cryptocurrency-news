
#' Replace Symbols
#'
#' Replaces '+' to '-', '/' to '_' and '=' to ''
#'
#' @param str a character vector.
#'
#' @return
#' @export
#'
#' @examples
#' str_replace_symbols("a+b-c/d_e=f")
str_replace_symbols <- function(str) {
  str <- gsub("+", "-", str, fixed = TRUE)
  str <- gsub("/", "_", str, fixed = TRUE)
  str <- gsub("=", "", str, fixed = TRUE)
  str
}



#' curl_getinfo
#'
#' curl_getinfo
#'
#' @param ch a curl handler.
#'
#' @return list()
#' @export
curl_getinfo <- function(ch) {
  list(
     url = ch$url
    ,content_type = ch$type
    ,http_code = ch$status_code
    ,header_size = as.numeric(object.size(rawToChar(ch$headers)))
    ,request_size = as.numeric(object.size(rawToChar(ch$content)))
    ,filetime = "DON'T KNOW HOW TO RETRIEVE THIS INFO"
    ,ssl_verify_result = "DON'T KNOW HOW TO RETRIEVE THIS INFO"
    ,redirect_count = ch$times['redirect']
    ,total_time = ch$times['total']
    ,namelookup_time = ch$times['namelookup']
    ,connect_time = ch$times['connect']
    ,pretransfer_time = ch$times['pretransfer']
    ,size_download = as.numeric(object.size(rawToChar(ch$content)))
    ,starttransfer_time = ch$times['starttransfer']
  )
}
