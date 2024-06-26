#include "../../../include/components/backend/networkInterfaces.hpp"
#include <pcap.h>

std::vector<std::string> getEthernetAdapters() {
    pcap_if_t *alldevs;
    char errbuf[PCAP_ERRBUF_SIZE];
    std::vector<std::string> interfaces;

    if (pcap_findalldevs(&alldevs, errbuf) == -1) {
        interfaces.push_back("Błąd podczas wyszukiwania urządzeń");
        return interfaces;
    }

    for (pcap_if_t *d = alldevs; d; d = d->next) {
        interfaces.push_back(d->name);
    }
    pcap_freealldevs(alldevs);
    return interfaces;
}
