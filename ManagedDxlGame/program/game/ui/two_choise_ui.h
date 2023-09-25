#pragma once
#include "../base/ui_select_cmd_base.h"


// �R�}���h�̎��
enum class TwoChoiseCmd {
	TCC_BEGIN = -1,
	TCC_YES,
	TCC_NO,
	TCC_END
};

// �u�͂��v���u�������v��I������N���X
class TwoChoiseUI : public SelectUIBase {
public:
	TwoChoiseUI(const tnl::Vector3& pos);
	~TwoChoiseUI();

	void update(float delta_time) override;
	void draw() override;

	inline const TwoChoiseCmd& getSelectCmd() { return select_cmd_; }		// �I�𒆂̃R�}���h��Ԃ��B

private:

	TwoChoiseCmd select_cmd_;						// �I�𒆂̃R�}���h

	// �R�}���h�e�L�X�g
	std::string cmd_str_[static_cast<int>(TwoChoiseCmd::TCC_END)];

	tnl::Vector3 cmd_pos_;							// �R�}���h�e�L�X�g�̕\���ʒu

};