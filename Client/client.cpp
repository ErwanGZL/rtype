//
// Created by erwan on 10/6/23.
//

#include "client.h"
#include "Elements/Image.h"
#include "Scenes/Background.h"
#include "Scenes/LobbyList.h"
#include "Scenes/Login.h"
#include "net_message.h"

void client::start()
{
    if (!_build) {
        build();
    }
    while (_engine.isOpen()) {
        _engine.update();
        _bg->update();
    }
}

void client::build()
{
    std::cout << "[CLIENT] Building resources..." << std::endl;
    _engine.init();
    _window = _engine.createEntity();
    _window->addComponent(new Haze::Window(800, 600));

    _bg = std::make_unique<Background>(_engine);
    _bg->build();

    _login = std::make_unique<Login>(_engine, [this](int) {
        auto name = _login->get<TextInput>("name")->getValue();
        auto ip = _login->get<TextInput>("ip")->getValue();
        auto port = _login->get<TextInput>("port")->getValue();
        if (name.empty() || ip.empty() || port.empty()) return;
        connect(ip, static_cast<uint16_t>(std::stoul(port)));
    });
    //    _login->build();

    _lobbyList = std::make_unique<LobbyList>(_engine, [this](int) {
        std::cout << "Join" << std::endl;
    });
    _lobbyList->build();

    _build = true;
    std::cout << "[CLIENT] Build completed!" << std::endl;
}

//// TCP Events
//while (!getIncoming().empty()) {
//    network::message<lobby> msg = getIncoming().pop_front().content;
//    switch (msg.header.id) {
//        case lobby::data_channel: {
//            if (!_spectator) {
//                asio::ip::udp::endpoint peer;
//                msg >> peer;
//                peer = udp::endpoint(asio::ip::make_address(_login->getIp()), peer.port());
//                std::cout << "[PEER]: " << peer << std::endl;
//                _spectator = std::make_unique<spectator>(_context, _engine);
//                _spectator->addPeer(peer);
//                _startButton->getEntity().addComponent(new Haze::Hide);
//
//                network::datagram<protocol::data> data(protocol::data::join);
//                _spectator->sendTo(data, peer);
//
//                std::cout << "send join" << std::endl;
//            }
//            break;
//        }
//    }
//}


//if (_spectator) {
//    //            std::cout << "[INBOX] " << _game->getIncoming().count() << std::endl;
//    _spectator->update(50, false);
//    if (_spectator->aliveCD.IsReady()) {
//        _spectator->aliveCD.Activate();
//        _spectator->sendAll(network::datagram<protocol::data>(protocol::data::alive));
//        std::cout << "[GAME] sent Alive" << std::endl;
//    }
//}
