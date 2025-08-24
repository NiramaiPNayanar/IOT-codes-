# coap_client.py
import asyncio
from aiocoap import Message, GET, Context

async def main():
    protocol = await Context.create_client_context()

    req = Message(code=GET, uri='coap://127.0.0.1/hello') 
       
    try:
        res = await protocol.request(req).response 
        print("Response from server:", res.payload.decode())
    except Exception as e:
        print("Error:", e)

if __name__ == "__main__":
    asyncio.run(main())                        
