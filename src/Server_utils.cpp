#include "../include/Server.hpp"

void    Server::sendCgiResponse(int client_fd, int pos)
{
    if (send(client_fd, Reqmap[client_fd].cgi_content.c_str(), Reqmap[client_fd].cgi_content.size(), 0) <= 0)
        close_connexion(client_fd, pos);
    Msg::logMsg(LIGHT_BLUE, CONSOLE_OUTPUT, "client %d reponse envoyer with HTTP code : %s", client_fd, Reqmap[client_fd].http_code.c_str());
    Reqmap[client_fd].request = "";
    Reqmap[client_fd].method = "";
    Reqmap[client_fd].cgi_state = 0;
    Reqmap[client_fd].cgi_content = "";
    Reqmap[client_fd].connexion = "";
    Reqmap[client_fd].content_length = "";
    Reqmap[client_fd].content_type = "";
    Reqmap[client_fd].body = "";
    Reqmap[client_fd].content_type = "";
    Reqmap[client_fd].FilePath = "";
    Reqmap[client_fd].data.clear();
    close_connexion(client_fd, pos);
}


std::string Server::getContentType(const std::string& file_path) {
    if (file_path.substr(file_path.size() - 5) == ".html") return "text/html; charset=UTF-8";
    if (file_path.substr(file_path.size() - 3) == ".py") return "text/html";
    if (file_path.substr(file_path.size() - 4) == ".css") return "text/css";
    if (file_path.substr(file_path.size() - 3) == ".js") return "application/javascript";
    if (file_path.substr(file_path.size() - 4) == ".jpg" || file_path.substr(file_path.size() - 5) == ".jpeg") return "image/jpeg";
    if (file_path.substr(file_path.size() - 4) == ".png") return "image/png";
    if (file_path.substr(file_path.size() - 1) == "/") return "text/html";
    return "multipart/form-data"; // ANCIENNEMENT text/html;
}