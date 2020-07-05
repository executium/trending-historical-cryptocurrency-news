'''

	Endpoint: public/trending-news-source-impact
	Name: Trending News Source Impact

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
endpoint = 'public/trending-news-source-impact'

# Only one parameter
payload = {'source_contains':''}

result = obj.send(endpoint, payload, dict())

print(json.dumps(result['returned'], indent=4))
