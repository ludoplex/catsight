#include <Common.h>
#include <Helpers/CodeButton.h>
#include <Inspector.h>
#include <Tabs/CodeTab.h>

#include <hello_imgui.h>

void Helpers::CodeButton(Inspector* inspector, uintptr_t p)
{
	static s2::list<CodeTab*> _codeTabs;

	ImGui::PushID((void*)p);

	if (ImGui::Button(ICON_FA_CODE_BRANCH, ImVec2(30, 0))) {
		_codeTabs.clear();
		for (auto tab : inspector->m_tabs) {
			auto codeTab = dynamic_cast<CodeTab*>(tab);
			if (codeTab != nullptr) {
				_codeTabs.add(codeTab);
			}
		}

		if (_codeTabs.len() == 0) {
			auto newTab = new CodeTab(inspector, "Code", p);
			newTab->GoTo(p);
			inspector->m_tabs.add(newTab);
		} else {
			ImGui::OpenPopup("CodeButtonPopup");
		}
	}
	if (ImGui::IsItemHovered()) {
		ImGui::SetTooltip("Code pointer: " POINTER_FORMAT, p);
	}

	if (ImGui::BeginPopup("CodeButtonPopup")) {
		ImGui::TextDisabled(POINTER_FORMAT, p);
		for (auto tab : _codeTabs) {
			ImGui::PushID(tab);
			if (ImGui::MenuItem(tab->GetLabel())) {
				tab->GoTo(p);
				tab->m_shouldFocus = true;
			}
			ImGui::PopID();
		}
		ImGui::Separator();
		if (ImGui::MenuItem(ICON_FA_PLUS " New code tab")) {
			auto newTab = new CodeTab(inspector, "Code", p);
			newTab->GoTo(p);
			inspector->m_tabs.add(newTab);
		}
		ImGui::EndPopup();
	}

	ImGui::PopID();
}
