#include "Shader.h"


void Shader::LoadRaytracing(const wchar_t* filePath)
{
	std::ifstream shaderFile(filePath);
	if (shaderFile.good() == false) {
		std::wstring errormessage = L"�V�F�[�_�[�t�@�C���̃I�[�v���Ɏ��s���܂����B\n";
		errormessage += filePath;
		MessageBoxW(nullptr, errormessage.c_str(), L"�G���[", MB_OK);
		std::abort();
	}

	std::stringstream strStream;
	strStream << shaderFile.rdbuf();
	std::string shader = strStream.str();
	//�V�F�[�_�[�̃e�L�X�g�t�@�C������ABLOB���쐬����B
	CComPtr<IDxcLibrary> dxclib;
	auto hr = DxcCreateInstance(CLSID_DxcLibrary, IID_PPV_ARGS(&dxclib));
	if (FAILED(hr)) {
		MessageBox(nullptr, L"DXCLIB�̍쐬�Ɏ��s���܂����B", L"�G���[", MB_OK);
		std::abort();
	}
	CComPtr< IDxcIncludeHandler> includerHandler;
	hr = dxclib->CreateIncludeHandler(&includerHandler);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"CreateIncludeHandler�Ɏ��s���܂����B", L"�G���[", MB_OK);
		std::abort();
	}

	//dxc�R���p�C���̍쐬�B
	CComPtr<IDxcCompiler> dxcCompiler;
	hr = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&dxcCompiler));
	if (FAILED(hr)) {
		MessageBox(nullptr, L"dxc�R���p�C���̍쐬�Ɏ��s���܂����B", L"�G���[", MB_OK);
		std::abort();
	}
	//�\�[�X�R�[�h��BLOB���쐬����B
	uint32_t codePage = CP_UTF8;
	CComPtr< IDxcBlobEncoding> sourceBlob;
	hr = dxclib->CreateBlobFromFile(filePath, &codePage, &sourceBlob);
	if (FAILED(hr)) {
		MessageBox(nullptr, L"�V�F�[�_�[�\�[�X��Blob�̍쐬�Ɏ��s���܂����B", L"�G���[", MB_OK);
		std::abort();
	}

	CComPtr<IDxcIncludeHandler> dxcIncludeHandler;
	dxclib->CreateIncludeHandler(&dxcIncludeHandler);
	const wchar_t* args[] = {
		L"-I Assets\\shader",
	};
	//�R���p�C���B
	CComPtr<IDxcOperationResult> result;
	hr = dxcCompiler->Compile(
		sourceBlob, // pSource
		filePath, // pSourceName
		L"",		// pEntryPoint
		L"lib_6_3", // pTargetProfile
		args, 1, // pArguments, argCount
		nullptr, 0, // pDefines, defineCount
		dxcIncludeHandler, // pIncludeHandler
		&result); // ppResult
	if (SUCCEEDED(hr)) {
		result->GetStatus(&hr);
	}

	if (FAILED(hr))
	{
		if (result)
		{
			CComPtr<IDxcBlobEncoding> errorsBlob;
			hr = result->GetErrorBuffer(&errorsBlob);
			if (SUCCEEDED(hr) && errorsBlob)
			{
				std::string errormessage = "Compilation failed with errors:\n%hs\n";
				errormessage += (const char*)errorsBlob->GetBufferPointer();
				MessageBoxA(nullptr, errormessage.c_str(), "�G���[", MB_OK);

			}
		}
		// Handle compilation error...
	}
	else {
		result->GetResult(&m_dxcBlob);
	}
}
