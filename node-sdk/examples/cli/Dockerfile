FROM node:lts

ENV NODE_ENV=production

COPY . /app

WORKDIR /app

RUN yarn install

ENTRYPOINT ["./index.js"]
