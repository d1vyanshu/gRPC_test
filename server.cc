#include<string>

#include<grpcpp/grpcpp.h>

#include "intsquare.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using intsquare::IntSquare;
using intsquare::IntRequest;
using intsquare::IntReply;

class SquareServiceImplementation final : public IntSquare::Service {
    Status sendRequest(ServerContext* context, const IntRequest* request, IntReply* reply) override {
        int x = request->x();
        reply->set_xsq(x*x);

        return Status::OK;
    }
};

void Run() {
    std::string address("0.0.0.0:5000");
    SquareServiceImplementation service;

    ServerBuilder builder;

    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on port:" << address << std::endl;

    server->Wait();
}

int main(int argc, char** argv) {
    Run();

    return 0;
}