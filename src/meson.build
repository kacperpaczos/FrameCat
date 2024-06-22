dependency('pcap', required: true)
dependency('ftxui', required: true)

executable('ethernetcap', 
  'main.cpp', 
  'components/ui/ethernetAdapterList.cpp', 
  'view/interfaceListView.cpp', 
  dependencies: [dependency('pcap'), dependency('ftxui')]
)
