
'''

	Endpoint: public/trending-news-watchlist
	Name: Trending News Watchlist

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
endpoint = 'public/trending-news-watchlist'

# No parameters required
payload = {}

result = obj.send(endpoint, payload, dict())

print(json.dumps(result['returned'], indent=4))