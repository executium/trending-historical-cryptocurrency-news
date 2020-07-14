class ApiAccess
  attr_reader :version,
              :domain,
              :useragent,
              :path,
              :url,
              :endpoints,
              :timeout

  def initialize(api_key, api_secret, api_version = 'v1')
    @api_key     = api_key
    @api_secret  = api_secret
    @api_version = api_version
    @version     = 2
    @domain      = 'https://trendingnews.executium.com'
    @useragent   = 'API v2 (Ruby)'
    @path        = ''
    @url         = ''
    @endpoints   = {}
    @timeout     = 3000
  end

  def set_path(received_path)
    @path = received_path
  end

  # {
  #   api_key: 'some_random_api_key',
  #   api_secret: 'some_random_api_secret',
  #   api_version: 2,
  #   version: 2,
  #   ...
  # }
  def config(configuration_hash)
    configuration_hash.each do |key, value|
      instance_variable_set("@#{key}", value)
    end
  end

  def get_api_url(received_path)
    [@domain, '/api/v', @version, '/', received_path].join('')
  end

  def get_config
    {
      api_key:     @api_key,
      api_secret:  @api_secret,
      api_version: @api_version,
      version:     @version,
      domain:      @domain,
      useragent:   @useragent,
      path:        @path,
      url:         @url,
      endpoints:   @endpoints,
      timeout:     @timeout
    }
  end

  def get_endpoints
    @endpoints
  end

  def decode(result)
    JSON.parse(result)
  end

  def nonce
    Integer(Float("%10.6f" % Time.now) * 10_000_000.0)
  end

  def send(path, input, payload)
    set_path(path)
    post(input, payload)
  end

  def endpoints(input)
    set_path('system/ep')
    @endpoints = post(input, {})[:returned]['data']
  end

  def replace_multiple_characters(string)
    string.gsub('+', '-').gsub('/', '_').gsub('=', '').gsub("\n", '')
  end

  def auth
    b01 = replace_multiple_characters(Base64.encode64('{"typ":"JWT","alg":"HS256"}'))
    b02 = replace_multiple_characters(Base64.encode64({"nonce":nonce}.to_json))
    sig = OpenSSL::HMAC.digest(OpenSSL::Digest.new('sha256'), @api_secret, "#{b01}.#{b02}")
    b03 = replace_multiple_characters(Base64.encode64(sig))

    [b01, b02, b03].join('.')
  end

  def post(input, payload)
    result   = RestClient::Request.new({
        method:  :post,
        url:     get_api_url(@path),
        payload: URI.encode_www_form(input),
        timeout: @timeout / 1000,
        headers: {
          'User-Agent':    @useragent,
          'Content-Type':  'application/x-www-form-urlencoded',
          'Key':           " #{@api_key}",
          'Authorization': " #{auth}"
        }
    }).execute do |response, request, result|
      case response.code
      when 400
        { 'success': false, 'returned': decode(response.to_str) }
      when 200
        if response.to_str.empty?
          { 'success': false, 'returned': response.to_str }
        else
          { 'success': true, 'returned': decode(response.to_str) }
        end
      when 301, 302, 307
        response.follow_redirection
      else
        fail "Invalid response #{response.to_str} received."
      end
    end

    result
  end
end
