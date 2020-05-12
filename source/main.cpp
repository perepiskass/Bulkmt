#include "version_lib.h"
#include "data.h"

#include <csignal>
#include <thread>

std::shared_ptr<DataIn> bulkPtr;

size_t checkArg(int, char**);

void signalFunction(int sig)
{
  std::cin.clear();
  std::cout << std::endl;
  if (sig) 
  {
    if (!bulkPtr->getBulk().first.empty()) bulkPtr->notify();
  }
  while(!bulkPtr->bulkQ.empty()) continue;
  exit(0);
}

int main(int argc, char *argv[]) 
{
  try
  {
    auto bulk_size = checkArg(argc,argv);   ///< устанавливаем значение размера блока для команд

    bulkPtr = std::shared_ptr<DataIn> {new DataIn(bulk_size)};
    std::shared_ptr<DataToConsole> console{new DataToConsole(bulkPtr)};
    std::shared_ptr<DataToFile> file{new DataToFile(bulkPtr)};

    constexpr size_t count_thread = 4;    ///< общее колличество потоков в программе.
    Logger::getInstance().init(count_thread);

    std::thread log([console](){console->update(1);});
    std::thread file1([file](){file->update(2);});
    std::thread file2([file](){file->update(3);});

    log.detach();
    file1.detach();
    file2.detach();
    
    signal(SIGINT,signalFunction);

    std::string str;
    while(getline(std::cin,str))
    {
      bulkPtr->setData(std::move(str));
      std::cin.clear();
    }

  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
    return 0;
}
