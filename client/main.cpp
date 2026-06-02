#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<cstring>

int send_msg(const int fd,const std::string msg){
    if(msg.size()>255){
        std::cout<<"Message size too big";
        exit(1);
    }
    uint8_t len=msg.size();
    if(send(fd,&len,1,0)==-1){
        perror("send failed");
        exit(1);
    }
    

    if(send(fd,msg.data(),(int)len,0)==-1){
        perror("send failed");
        exit(1);
    }
    return 0;
}

int main(){
    int client_socket;
    if((client_socket=socket(AF_INET,SOCK_STREAM,0))==-1){
        perror("socket creation failed");
        exit(1);
    }

    sockaddr_in server_address;
    server_address.sin_family=AF_INET;
    server_address.sin_port=htons(5000);

    if(inet_pton(AF_INET,"127.0.0.1",&server_address.sin_addr)<=0){
        perror("inet pton failed");
        exit(1);
    }

    if(connect(client_socket,(struct sockaddr*)&server_address,sizeof(server_address))!=0){
        perror("Connection Error");
        exit(1);
    }
    
    if(send_msg(client_socket,"Hello server")!=0){
        perror("send failed");
        exit(1);
        
    }
    
    // const char* msg="Hello server";
    // if(send(client_socket,msg,strlen(msg),0)==-1){
    //     perror("send failed");
    //     exit(1);
    // }
    
    // char buffer[1024];
    // int bytes=recv(client_socket,buffer,sizeof(buffer)-1,0);
    // if(bytes==-1){
    //     perror("receive failed");
    //     exit(1);
    // }
    // buffer[bytes]='\u0000';
    // std::cout<<buffer<<std::endl;


    close(client_socket);
    return 0;

}