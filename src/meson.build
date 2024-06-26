dependency('pcap', required: true)
dependency('ftxui', required: true)

executable('ethernetcap', 
  'main.cpp',
  'components/ui/ethernetAdapterList.cpp',
  'components/ui/mainMenu.cpp',
  'views/interfaceListView.cpp',
  'views/mainMenuView.cpp',
  'components/ui/viewManager.cpp',
  'components/backend/networkInterfaces.cpp',
  dependencies: [dependency('pcap'), dependency('ftxui')]
)
