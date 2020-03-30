# Vastchain
Welcome to Vastchain public source repo.

## For Production

The blockchain RPC interface is not designed for the Internet but for local network. And since RPC interface don't provide features like rate limitation's, security checks and so on. It highly suggests anyone who wants to run a node to use a reverse proxy server like nginx to serve all the requests.
