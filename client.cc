#include<string>

#include<grpcpp/grpcpp.h>
#include "intsquare.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using intsquare::IntSquare;
using intsquare::IntReply;
using intsquare::IntRequest;

class IntSqaureClient {
    public:
        IntSqaureClient(std::shared_ptr<Channel> channel) : stub_(IntSquare::NewStub(channel)) {}
    
    int sendRequest(int x) {
        IntRequest request;
        request.set_x(x);
        ClientContext context;

        IntReply reply;

        Status status = stub_->sendRequest(&context, request, &reply);

        if(status.ok()) {
            return reply.xsq();
        }
        else {
            std::cout << status.error_code() << ": " << status.error_message() << std::endl;
            return -1;
        }
    }

    private:
        std::unique_ptr<IntSquare::Stub> stub_;
};

void Run() {
    std::string address("0.0.0.0:5000");
    IntSqaureClient client(grpc::CreateChannel(address, grpc::InsecureChannelCredentials()));

    int response, x;

    std::cin>>x;

    response = client.sendRequest(x);

    std::cout<<"Answer received: " << response <<std::endl;

}

int main(int argc, char** argv) {
    Run();

    return 0;
}