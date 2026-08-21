import Application;

int main(int argc, char *argv[])
{
	const auto ptr{Application::Init(argc, argv)};
	return ptr->Exec();
}
