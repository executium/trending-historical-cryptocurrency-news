'''

	Endpoint: public/trending-news-data
	Name: Trending News Data

'''
import sys
import json

sys.path.insert(1, '../src')
	
# Include config and class
from config import key, secret
from Class import ApiAccess

# Declare your key and secret
obj = ApiAccess(key, secret)

# Declare endpoint
endpoint = 'public/trending-news-data'

# Parameters required
payload = {'date': '2020-07-04'}

result = obj.send(endpoint, payload, dict())

print(json.dumps(result['returned'], indent=4))