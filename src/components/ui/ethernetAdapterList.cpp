#include "../../../include/components/ui/ethernetAdapterList.hpp"
#include <pcap.h>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <thread>
#include <vector>
#include <string>
#include <chrono>

std::vector<std::string> get_network_interfaces() {
    pcap_if_t *alldevs;
    char errbuf[PCAP_ERRBUF_SIZE];
    std::vector<std::string> interfaces;

    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
        interfaces.push_back("Error finding devices");
        return interfaces;
    }

    for (pcap_if_t *d = alldevs; d; d = d->next) {
        interfaces.push_back(d->name);
    }

    pcap_freealldevs(alldevs);
    return interfaces;
}

void capture_packets(const std::string& interface) {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_t* handle = pcap_open_live(interface.c_str(), BUFSIZ, 1, 1000, errbuf);
    if (handle == nullptr) {
        // Wyświetl błąd w FTXUI
        auto screen = ftxui::ScreenInteractive::Fullscreen();
        auto renderer = ftxui::Renderer([&] {
            return ftxui::text("Couldn't open device " + interface + ": " + errbuf) | ftxui::border;
        });
        screen.Loop(renderer);
        return;
    }

    std::vector<std::string> packet_list;
    auto screen = ftxui::ScreenInteractive::Fullscreen();
    auto renderer = ftxui::Renderer([&] {
        std::vector<ftxui::Element> elements;
        for (const auto& packet : packet_list) {
            elements.push_back(ftxui::text(packet));
        }
        return ftxui::vbox(elements) | ftxui::border;
    });

    std::thread capture_thread([&] {
        pcap_loop(handle, 0, [](u_char* args, const struct pcap_pkthdr* header, const u_char* packet) {
            auto packet_list = reinterpret_cast<std::vector<std::string>*>(args);
            packet_list->push_back("Captured a packet with length of [" + std::to_string(header->len) + "]");
        }, reinterpret_cast<u_char*>(&packet_list));
    });

    std::thread render_thread([&] {
        while (true) {
            screen.PostEvent(ftxui::Event::Custom);
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    });

    screen.Loop(renderer);
    pcap_close(handle);
    capture_thread.join();
    render_thread.detach();
}