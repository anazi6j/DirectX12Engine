#pragma once


class DescriptorPool
{
	std::unique_ptr<DirectX::DescriptorHeap> m_SRVCAVUAVHEAPS;

	std::unique_ptr<DirectX::DescriptorHeap> m_Samplers;

	//RTV,DSV�͑S�R�m��Ȃ��̂ŕ׋����Ă����������B
public:
	DescriptorPool() {};
	DescriptorPool(ID3D12Device* device);
};

