import FailHandler;

int main(int argc, char *argv[])
{
	const auto ptr{FailHandler::Init(argc, argv)};
	return ptr->Exec();
}
