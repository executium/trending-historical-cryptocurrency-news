require 'base64'
require 'uri'
require 'json'
require 'openssl'
require 'rubygems'

gem 'rest-client', '~> 2.1.0'

puts "If it takes a little longer we are installing RestClient"
puts "Please wait!"

require 'rest-client'

load 'class.rb'
load 'config.rb'

api_access       = ApiAccess.new(@api_key, @api_secret)
endpoint         = 'public/trending-news-data'
input            = { 'date' => '2020-07-13' }

puts api_access.send(endpoint, input, {})
