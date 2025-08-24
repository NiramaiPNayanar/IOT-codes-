import asyncio
from aiocoap import Context, Message, GET

async def send_get(uri):
    protocol = await Context.create_client_context()
    req = Message(code=GET, uri=uri)

    try:
        res = await protocol.request(req).response
        print(f"Response from {uri}: {res.payload.decode()}")
    except Exception as e:
        print(f" Error contacting {uri}:", e)

async def main():
    await send_get('coap://127.0.0.1/hello')
    await send_get('coap://127.0.0.1/time')
    

if __name__ == "__main__":
    asyncio.run(main())