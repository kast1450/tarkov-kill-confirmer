#include <Windows.h>
#include <iostream>
#include <filesystem>
#include <string>
#include <chrono>
#include <ctime>

namespace fs = std::filesystem;

int main()
{
	SetConsoleTitleA("Escape from Tarkov: Kill Confirmer");

	printf("!!! WARNING !!!\nEven though this software does not interact with Escape from Tarkov in any way, you may be risking a ban for using this software.\nAlso, it may be inaccurate, since all it's doing is listening for file changes in the NVIDIA directory.\n\n");

	HWND console = GetConsoleWindow();

	char directory[MAX_PATH];
	sprintf_s(directory, "%ws%s", fs::temp_directory_path().c_str(), "Highlights\\Escape From Tarkov");

	if (!fs::exists(directory))
	{
		printf("%s doesn't exist!\nPlease create that folder!\n", directory);
		getchar();
		return 0;
	}
	printf("Highlights path is: %s\n", directory);

	printf("Starting to look for new files...\n\n");

	int total_kills = 0;
	while (true)
	{
		WaitForSingleObject(FindFirstChangeNotificationA(directory, FALSE, FILE_NOTIFY_CHANGE_FILE_NAME), INFINITE);
		total_kills++;
		std::time_t kill_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		printf("Kill confirmed(?) at %sTotal kills: %i\n\n", std::ctime(&kill_time), total_kills);
		Beep(523, 200);
		Sleep(50);
	}
	
	return 0;
}
