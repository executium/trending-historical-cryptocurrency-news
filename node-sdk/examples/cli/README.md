## Installation
`yarn install`

## Usage
```bash
index.js <command>

Commands:
  index.js request <path> [input]           request command
  [payload]

Options:
  --help                 Show help                                     [boolean]
  --version              Show version number                           [boolean]
  --apiKey, --key        API Key                             [string] [required]
  --apiSecret, --secret  API Secret                          [string] [required]
```

### Example
```bash
./index.js request public/trending-news-data '{ "date": "2020-07-05" }' --apiKey=free --apiSecret=free
```
### Docker

#### Build
`docker build -t examples-cli .`
#### Run
```bash
docker run --rm examples-cli request public/trending-news-data '{ "date": "2020-07-05" }' --apiKey=free --apiSecret=free
```
