#include "gui.h"
#include "global.h"
#include "imgui.h"
#include "Utils.h"
#include "utils/gui-util.hpp"

void Gui::Render()
{
    auto& vars = Vars::GetInstance();

    ImGui::Begin("##Taiga74164", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
    {
        // Header Section
        ImGui::BeginGroup();
        {
            ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
            GuiUtil::CenterText(Utils::GenerateRandomString(10).c_str(), 0, 0);
            ImGui::Spacing();
            ImGui::Spacing();
            ImGui::PopStyleColor();
        }
        ImGui::EndGroup();

        // Left Menu
        ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
        ImGui::BeginChild("##LeftSide", ImVec2(100, GuiUtil::GetY()), true);
        ImGui::PopStyleColor();
        {
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);

            const ImVec4 active = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
            const ImVec4 inactive = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);

            auto createMenuButton = [&](const char* name, int tab) {
                ImGui::PushStyleColor(ImGuiCol_Button, m_MenuTab == tab ? active : inactive);
                if (ImGui::Button(name, ImVec2(80, 22))) {
                    m_MenuTab = tab;
                }
                ImGui::PopStyleColor();
                };

            createMenuButton("Features", 0);
            createMenuButton("Misc", 1);
        }
        ImGui::EndChild();

        GuiUtil::LineVertical();

        // Right Content
        ImGui::PushStyleColor(ImGuiCol_ChildBg, IM_COL32(0, 0, 0, 0));
        ImGui::BeginChild("##RightSide", ImVec2(GuiUtil::GetX(), GuiUtil::GetY()), true);
        ImGui::PopStyleColor();

        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImGuiCol_Button ? active : inactive);

        switch (m_MenuTab)
        {
        case 0: // Features
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
            ImGui::BeginGroup();

            ImGui::CheckboxFill("Instant Regen", &vars.InstantRegen.value()); HELPMAKER("Press Run");
            ImGui::CheckboxFill("No Cooldown", &vars.NoCooldown.value());
            ImGui::CheckboxFill("No Cooldown Shadow", &vars.NoCooldownShadow.value()); HELPMAKER("Enable only if you have shadow feature available");
            ImGui::CheckboxFill("God Mode", &vars.GodMode.value());
            ImGui::CheckboxFill("Kill Aura", &vars.KillAura.value());
            ImGui::CheckboxFill("Damage Hack", &vars.DamageHack.value());
            if (vars.DamageHack.value()) {
                ImGui::SliderInt("Value", &vars.DamageHackValue.value(), 1000, 10000000, "%d");
            }
            ImGui::CheckboxFill("Mission Time", &vars.MissionTime.value()); HELPMAKER("Make sure this is enabled before starting a mission");
            if (vars.MissionTime.value()) {
                ImGui::SliderInt("Time (ms)", &vars.MissionTimeMs.value(), 180000, 3600000, "%d");
            }
            ImGui::CheckboxFill("Time Scale", &vars.TimeScale.value());
            if (vars.TimeScale.value()) {
                ImGui::SliderFloat("Speed", &vars.TimeScaleSpeed.value(), 1.0f, 10.0f, "%.1f");
            }

            ImGui::EndGroup();
            ImGui::PopStyleVar();
            break;

        case 1: // Misc
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
            ImGui::BeginGroup();

            ImGui::CheckboxFill("FPS Unlock", &vars.FPSUnlock.value());
            if (vars.FPSUnlock.value()) {
                ImGui::SliderInt("FPS", &vars.FPSValue.value(), 5, 360, "%d");
            }
            ImGui::CheckboxFill("Fov Changer", &vars.FovChanger.value());
            if (vars.FovChanger.value()) {
                ImGui::SliderFloat("Fov", &vars.Fov.value(), 1.0f, 360.0f, "%.1f");
            }
            ImGui::CheckboxFill("Skip Intro Movie", &vars.SkipIntroMovie.value()); HELPMAKER("This will skip the intro movie when you start the game");
            ImGui::CheckboxFill("Disable Web View", &vars.DisableWebView.value()); HELPMAKER("Disables WebView pop-up every time you enter the game");

            ImGui::EndGroup();
            ImGui::PopStyleVar();
            break;
        }

        ImGui::PopStyleColor();
        ImGui::EndChild();
    }
    ImGui::End();
}
