## Without Docker

### Installation
`yarn install`

### Starting the server
```bash
API_KEY=free API_SECRET=free yarn start
```
## Docker

### Build
`docker build -t examples-express .`
### Start
```bash
docker run -p 3000:3000 -e API_KEY=free -e API_SECRET=free -d examples-express
```

## Testing the service
Navigate to this [link](http://localhost:3000/?path=/public/trending-news-data&input={%20%22date%22:%222020-07-02%22})

```
http://localhost:3000/?path=/public/trending-news-data&input={%20%22date%22:%222020-07-02%22}
```

