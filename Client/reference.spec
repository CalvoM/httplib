Digest Auth:
    From server:
        Header: WWW-Authenticate
        Possible values:
            realm: string
            domain: space separated list of strings of URI
            nonce: string (hex or base64)
            opaque: string (hex or base64)
            stale: boolean
            algorithm: string
            qop: comma separated list of strings
            charset: string(optional)
            userhash: boolean(optional)
    From client:
        Header: Authorization
        Value: Digest username="username", realm="realm", nonce="nonce", uri="uri",
            response="response", qop=qop, nc=nc, cnonce="cnonce",
            opaque="opaque", algorithm="algorithm",
            message-qop=message-qop, charset=charset, userhash=userhash