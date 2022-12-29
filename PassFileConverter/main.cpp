// Author: Lucas Oliveira Vilas-Bôas
// Year: 2022
// Repository: 

#include "DataLoader.h"
#include "HelperLib.h"

int main()
{
    std::unique_ptr<DataLoader> dataLoader = std::make_unique<DataLoader>();    
    
    try
    {
        const std::string input_path = Helper::askQuestion("input file path: ");
        dataLoader->loadFile(input_path, LoginDataOrigin::Kapersky);
        
        const std::string output_path = Helper::askQuestion("output file path: ");
        dataLoader->saveFile(output_path, LoginDataOrigin::Google);

        if (dataLoader->hasInvalidData())
        {
            const std::string invalid_output_path = Helper::askQuestion("invalid data output file path: ");
            dataLoader->exportInvalidData(invalid_output_path);
        }
    }
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

    dataLoader.reset();

	// 0: No | 1: Yes | Default: Undefined, ask again
    const auto restart_lambda = [] () -> std::uint8_t
    {
        if (const std::string restart_app = Helper::askQuestion("restart app? (Y/N): ");
            restart_app.contains("y") || restart_app.contains("Y"))
        {
            return 1;
        }
        else if (restart_app.contains("n") || restart_app.contains("N"))
        {
            return 0;
        }
        else
        {
            return -1;
        }
    };

    std::uint8_t restart_ans = restart_lambda();
	while (restart_ans != 1 && restart_ans != 0)
	{
		restart_ans = restart_lambda();
	}
    
    if (restart_ans == 1)
    {
        system("cls");
        
        return main();
    }
    else if (restart_ans == 0)
    {
        std::cout << std::endl;
        return 0;
    }
}