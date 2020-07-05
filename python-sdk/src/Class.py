import time
import base64
import json
import hmac 
import hashlib
import pycurl
import io
try:
    import urllib.parse as urllib
except ImportError:
    import urllib
import certifi

class ApiAccess():
    '''
    @param string $api_key       Your API key obtained from executium.com
    @param string $api_secret    Your API secret obtained from executium.com
    '''
    def __init__(self, api_key, api_secret, api_version = 'v1'):
        self.__api_key = api_key
        self.__api_secret = api_secret

        self.version = 2
        self.domain = 'https://trendingnews.executium.com'
        self.useragent = 'Trending News Python API v2'
        self.path = ''
        self.url = ''
        self.endpointsVar = []
        self.timeout = 30000
        self.conf = dict()

    def config(self, conf):
        for k, v in conf.items():
            self.conf[k] = v
    
    def get_api_url(self, path):
        return "{}/api/v{}/{}".format(self.domain, self.version, path)

    def set_path(self, path):
        self.path = path

    def get_config(self):
        return self.conf

    def endpoints(self, input):
        self.set_path('system/ep')
        ret = self.post(input, dict())
        self.endpointsVar = ret['returned']['data']

    def send(self, path, input, payload):
        self.set_path(path)
        return self.post(input, payload)

    def nonce(self):
        return round(time.time() * 10000000)

    def auth(self):
        self.payload['nonce'] = self.nonce()
        edits = [('+', '-'), ('/', '_'), ('=', '')]

        b01 = base64.b64encode('{"typ":"JWT","alg":"HS256"}'.encode('ascii')).decode('ascii')
        for search, replace in edits:
            b01 = b01.replace(search, replace)

        b02 = base64.b64encode(json.dumps(self.payload, separators=(',', ':')).encode('ascii')).decode('ascii')
        for search, replace in edits:
            b02 = b02.replace(search, replace)

        sig = hmac.new(self.__api_secret.encode(), "{}.{}".format(b01, b02).encode('ascii'), hashlib.sha256).digest()
        b03 = base64.b64encode(sig).decode('ascii')
        for search, replace in edits:
            b03 = b03.replace(search, replace)

        return "{}.{}.{}".format(b01, b02, b03)

    def post(self, input, payload):
        response = io.BytesIO()
        ch = pycurl.Curl()

        if ch is None:
            return {'code': 100, 'error': 'PYTHON-CURL not enabled'}
        else:
            self.payload = payload
            self.url = self.get_api_url(self.path)

            ch.setopt(pycurl.CAINFO, certifi.where())
            ch.setopt(ch.URL, self.url)
            ch.setopt(ch.HEADER, False)
            ch.setopt(ch.NOPROGRESS, True)
            ch.setopt(ch.TIMEOUT_MS, self.timeout)
            ch.setopt(ch.FOLLOWLOCATION, 1)
            ch.setopt(ch.USERAGENT, self.useragent)
            ch.setopt(ch.HTTPHEADER, ["Key: {}".format(self.__api_key), "Authorization: {}".format(self.auth())])
            ch.setopt(ch.WRITEFUNCTION, response.write)

            if(len(input) > 0):
                ch.setopt(ch.POST, len(input))
                ch.setopt(ch.POSTFIELDS, urllib.urlencode(input))

            ch.perform()
            ret = response.getvalue()
            out = {'success': False, 'returned': dict(), 'network_info': dict()}

            if not ret:
                out['success'] = False
                out['returned'] = ret
                out['network_info'] = self.get_curl_info(ch)
            else:
                out['success'] = True
                out['returned'] = self.decode(ret)
                out['network_info']= self.get_curl_info(ch)

            ch.close()
            response.close()

            return out
    
    def get_endpoints(self):
        return self.endpointsVar

    def decode(self, result):
        return json.loads(result)

    def get_curl_info(self, ch):
        return {
            "url": ch.getinfo(ch.EFFECTIVE_URL),
            "content_type": ch.getinfo(ch.CONTENT_TYPE),
            "http_code": ch.getinfo(ch.HTTP_CODE),
            "header_size": ch.getinfo(ch.HEADER_SIZE),
            "request_size": ch.getinfo(ch.REQUEST_SIZE),
            "ssl_verify_result": ch.getinfo(ch.SSL_VERIFYRESULT),
            "redirect_count": ch.getinfo(ch.REDIRECT_COUNT),
            "total_time": ch.getinfo(ch.TOTAL_TIME),
            "namelookup_time": ch.getinfo(ch.NAMELOOKUP_TIME),
            "connect_time": ch.getinfo(ch.CONNECT_TIME),
            "pretransfer_time": ch.getinfo(ch.PRETRANSFER_TIME),
            "size_upload": ch.getinfo(ch.SIZE_UPLOAD),
            "size_download": ch.getinfo(ch.SIZE_DOWNLOAD),
            "speed_download": ch.getinfo(ch.SPEED_DOWNLOAD),
            "speed_upload": ch.getinfo(ch.SPEED_UPLOAD),
            "download_content_length": ch.getinfo(ch.CONTENT_LENGTH_DOWNLOAD),
            "upload_content_length": ch.getinfo(ch.CONTENT_LENGTH_UPLOAD),
            "starttransfer_time": ch.getinfo(ch.STARTTRANSFER_TIME),
            "redirect_time": ch.getinfo(ch.REDIRECT_TIME),
            "primary_ip": ch.getinfo(ch.PRIMARY_IP),
            "primary_port": ch.getinfo(ch.PRIMARY_PORT),
            "local_ip": ch.getinfo(ch.LOCAL_IP)
        }
