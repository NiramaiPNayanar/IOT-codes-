import asyncio
from aiocoap import *
import aiocoap.resource as resource 
import datetime

class HelloResource(resource.Resource):
    async def render_get(self, request):        # handle get request 
        print("Received GET request")
        return Message(payload=b"Hello from aiocoap server!")


async def main():
    root = resource.Site()                              # tree that maps - router
    root.add_resource(('hello',), HelloResource())      # url , class to call 
    await Context.create_server_context(root, bind=('127.0.0.1', None))  
                # creates a server and binds to root port 5683

    print("CoAP server running at coap://localhost/hello")

    await asyncio.get_running_loop().create_future()  # keep running
        # gets the running async tasks and loops for ever 

if __name__ == "__main__":
    asyncio.run(main())         
    # creates a event loop and runs main - wait for async process to complete
