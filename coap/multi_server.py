import asyncio
from aiocoap import Message, Context
import aiocoap.resource as resource 
import datetime
import time

class HelloResource(resource.Resource):
    async def render_get(self, request):
        print("Received GET request")
        return Message(payload=b"Hello from aiocoap server!")

class TimeResource(resource.Resource):
    async def render_get(self, request):
        print("Received Time request")
        now = datetime.datetime.now().isoformat()
        print("[/time] GET ->", now)
        return Message(payload=now.encode())

async def main():
    root = resource.Site()
    root.add_resource(('hello',), HelloResource())
    root.add_resource(('time',), TimeResource())
    await Context.create_server_context(root, bind=('127.0.0.1', None))
   # print("CoAP server running at coap://localhost/hello")

    await asyncio.get_running_loop().create_future()  # keep running

if __name__ == "__main__":
    asyncio.run(main())
