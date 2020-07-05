'''

	Endpoint: public/trending-news-statistics
	Name: Trending News Statistics

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
endpoint = 'public/trending-news-statistics'

# No parameters required
payload = {}

result = obj.send(endpoint, payload, dict())

print(json.dumps(result['returned'], indent=4))