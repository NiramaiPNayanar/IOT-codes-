# coap_client.py
import asyncio
from aiocoap import *

async def main():
    protocol = await Context.create_client_context() # creates a client udp socket async

    req = Message(code=GET, uri='coap://127.0.0.1/hello')  # creates a get request msg 
   # req = Message(code=GET, uri='coap://127.0.0.1/.well-known/core') 
       
    try:
        res = await protocol.request(req).response              # gets the response
        print("Response from server:", res.payload.decode())
    except Exception as e:
        print("Error:", e)

if __name__ == "__main__":
    asyncio.run(main())                             # for async calls creates a event loop
