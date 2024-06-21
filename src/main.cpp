#include <pcap.h>
#include <iostream>
#include <vector>
#include <string>

void packetHandler(u_char *userData, const struct pcap_pkthdr* pkthdr, const u_char* packet) {
    std::cout << "Captured a packet with length: " << pkthdr->len << std::endl;
}

int main() {
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_if_t *interfaces, *temp;
    pcap_t *handle;
    std::vector<std::string> interfaceNames;

    // Znajdź wszystkie dostępne interfejsy
    if (pcap_findalldevs(&interfaces, errbuf) == -1) {
        std::cerr << "Error finding devices: " << errbuf << std::endl;
        return 1;
    }

    // Listuj wszystkie interfejsy
    int i = 0;
    for (temp = interfaces; temp; temp = temp->next) {
        std::cout << ++i << ": " << temp->name;
        if (temp->description) {
            std::cout << " (" << temp->description << ")";
        }
        std::cout << std::endl;
        interfaceNames.push_back(temp->name);
    }

    if (interfaceNames.empty()) {
        std::cerr << "No interfaces found! Make sure you have the necessary permissions." << std::endl;
        pcap_freealldevs(interfaces);
        return 1;
    }

    // Wybierz interfejs
    int choice;
    std::cout << "Wybierz interfejs (1-" << interfaceNames.size() << "): ";
    std::cin >> choice;

    if (choice < 1 || choice > interfaceNames.size()) {
        std::cerr << "Invalid choice!" << std::endl;
        pcap_freealldevs(interfaces);
        return 1;
    }

    // Otwórz wybrany interfejs do przechwytywania
    handle = pcap_open_live(interfaceNames[choice - 1].c_str(), BUFSIZ, 1, 1000, errbuf);
    if (handle == nullptr) {
        std::cerr << "Could not open device " << interfaceNames[choice - 1] << ": " << errbuf << std::endl;
        pcap_freealldevs(interfaces);
        return 1;
    }

    // Przechwytuj pakiety
    pcap_loop(handle, 10, packetHandler, nullptr);

    // Zwolnij zasoby
    pcap_freealldevs(interfaces);
    pcap_close(handle);
    return 0;
}