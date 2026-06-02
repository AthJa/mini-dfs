#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<cstring>

int recv_message(int fd,char* &buffer){
    uint8_t len=-1;

    if(recv(fd,&len,1,0)==-1){
        perror("recv failed");
        exit(1);
    }
    
    buffer=(char *)malloc(((int)len)+1);
    int bytes=0;
    while(bytes!=(int)len){
        int temp;
        if((temp=recv(fd,(buffer+bytes),len-bytes,0))==-1){
            perror("recv failed");
            exit(1);
        }
        bytes+=temp;
    }
    *(buffer+len)='\u0000';
    return 0;
}

int main(){
    int server_socket;
    if((server_socket=socket(AF_INET,SOCK_STREAM,0))==-1){
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
    
    if(bind(server_socket,(struct sockaddr*)&server_address,sizeof(server_address))!=0){
        perror("Bind failed");
        exit(1);
    }
    
    if(listen(server_socket,5)!=0){
        perror("listen failed");
        exit(1);
    }
    
    int client_socket;
    if((client_socket=accept(server_socket,nullptr,nullptr))==-1){
        perror("accept failed");
        exit(1);
    }

    char* buffer;
    if(recv_message(client_socket,buffer)!=0){
        perror("receive failed");
        exit(1);
    }
    
    std::cout<<buffer<<std::endl;
    
    // char* buffer;
    // int bytes=recv(client_socket,buffer,sizeof(buffer)-1,0);
    // if(bytes==-1){
    //     perror("receive failed");
    //     exit(1);
    // }
    // buffer[bytes]='\u0000';
    // std::cout<<buffer<<std::endl;
    
    // const char* msg="Hello server";
    // if(send(client_socket,msg,strlen(msg),0)==-1){
    //     perror("send failed");
    //     exit(1);
    // }

    close(client_socket);
    close(server_socket);
    return 0;
}