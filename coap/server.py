import asyncio
from aiocoap import Message, Context
import aiocoap.resource as resource 
import datetime

class HelloResource(resource.Resource):
    async def render_get(self, request):     
        print("Received GET request")
        return Message(payload=b"Hello from aiocoap server!")


async def main():
    root = resource.Site()                             
    root.add_resource(('hello',), HelloResource())    
    await Context.create_server_context(root, bind=('127.0.0.1', None))  

    print("CoAP server running at coap://localhost/hello")

    await asyncio.get_running_loop().create_future() 

if __name__ == "__main__":
    asyncio.run(main())         
