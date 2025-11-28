#include "typing_string.h"
#include <conio.h>
#include<bits/stdc++.h>
using namespace std;

#define PASSWORD "380"
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77

#include <windows.h>
#include <shellapi.h>

vector<string> pages = {
"�m�W:yuan\n�ʧO:Male\n�X�ͦ~��:2012/11/08\n�q��:0909090909\n�����Ҧr��:H123456789\n����:�a��\n�{�����}:NON\n��Ƶ{��:�j��(fake�A���L�Ǿ�)\n�M�~:�_�ۥͪ���\n���ˤH:����{\n�M���ˤH�����Y:��mai�{�Ѫ��B��\n�D¾¾��:����{�U�z\n�Ш|�I��:�Чڮa���̻���\n�u�@�g��:�L\n�ޯ�:������{���ߡA�ѰO���]\n�ۧڵ���:�١A�ڬOYuan�A�@�W�R���зN�P���q�P���a��C���M�ڪ��Ǿ��ݦ����ǡ����ˡ��A���ھ֦��@�����i�������M�~�ޯ�X�X�_�ۥͪ��ǡC�O�ݧڨ���ǤF�Ǥ���A�����o�O�D�`���ݪ��ǰݡA�u��ηQ���O�Ӳz�ѡC\n���M�ڨS�����g���u�@�g���A���ڦb��`�ͬ����n�֤F���ָg��A�ȱo�U�쭫���C\n���ӳW��: kop�a�x",
"�m�W:RYMOND\n�ʧO:�o�ˤl\n�X�ͦ~��:1999/10/20\n�q��:�L\n�����Ҧr��:A123542019\n����:�R��\n�{�����}:���c������\n��Ƶ{��:(�٨S)�ѳz�Ѿ�\n�M�~:�y�v�����A�W�߬B��\n���ˤH:�ڤ�E����\n�M���ˤH�����Y:���ڤ��O��E\n�D¾¾��:�M��u\n�Ш|�I��:�W�L��\n�u�@�g��:�s�W���Ʀ~�B�����M��Ʀ~\n�ޯ�:���ɥ����S�w�ϰ�\n�ۧڵ���:Ū�Ѥ��O�W�����z���ߤ@�覡�A�ҥH�ڨ�B�C���A���o�ˤ@�ө_�۪��ʺ��C�M��u�j���ֳ��వ�A���O�u���ڳo�˪��g����y�N���Ĳv���M��u�@�A���ڳ̦ۻ����O�ڱR�����ҬɡC\n���ӳW��:���ڬݰ��o�Ӻʺ����ǨƤ���A�ڴN�i�H�^��������¾�^���F�I",
"�m�W: �ܤ�\n�ʧO: �y�����N\n�X�ͦ~��: 1993�~3��22��\n�q��: 0987648648\n�����Ҧr��: Drinkwater\n����: ���y�Ȧ��S������\n�{�����}: �ȯS������\n��Ƶ{��: ���U�i��\n�M�~: �ܤ�\n���ˤH: �������溸�Z���S������D\n�M���ˤH�����Y: ͢���u�ƨ��v\n�D¾¾��: �O�Ф��u�u�@��\n�Ш|�I��: ��Ŭy�ʻ{��\n�u�@�g��: �j��`���y�ʺ޲z�H\n�ޯ�: �ϨC�ӤH�N���ܺ��õL����M\n�ۧڵ���: �@�ɤW�̯ª���\n���ӳW��: �����n�Q���i�A�ƻ򥼨ӳW�����Q����K\n\n",
"�m�W: ���\n�ʧO: �߯�\n�X�ͦ~��: �p��1912�~10��10��\n�q��:03-493-2476\n�����Ҧr��: Y333333333\n����: �߿�\n�{�����}: 100202 �O�_�������ϳ͹F�����j�D2��\n��Ƶ{��: ��Ƿ|�����p\n�M�~: �L\n���ˤH: ����\n�M���ˤH�����Y: �ۤv (*o�so)\n�D¾¾��: �ߥD\n�Ш|�I��: �L\n�u�@�g��: �p��F�`��T��ޤ��q\n�ޯ�: ��ߪ��W\n�ۧڵ���: �߫}\n���ӳW��: �C�Ѻ�25hr   �r(��W��)�r", 
"�m�W:Trip Star\n�ʧO:?(�}����)?(��������)\n�X�ͦ~��:2009/04/01\n�q��:0930790471\n�����Ҧr��:482-915-637\n����: �Ԫ��|�S�㰨�����|���±溸���~�ǤҾ|�S��\n�{�����}: �[���j���K�c��\n��Ƶ{��: �[���j���K�c�j�ǳդh\n�M�~: ��T�u�{�P�H�u���z\n\n�Ш|�I��:\n�p�Ǧܰ����b�[���j�h�ۦh�����A���Z�u��\n����NŪ���K�c�j�Ǹ�u�t�A�����h���ѥ[��ڵ{���v�����\n�Ӥh�P�դh�ұM��H�u���z�P�����ǲߡA�o���h�g���y���Z�פ�\n\n�u�@�g��:\n����h�a��ڬ�ޤ��q��ߡA�]�A�n��}�o�PAI��s\n�դh���~��A�������K�c�j��AI����Ǫ���s��\n�M�`��`�׾ǲߡB�۵M�y���B�z�έp�����ı��쪺�зs��s\n\n�ޯ�:\n��qPython�BC++�BJava�Φh�ص{���y��\n���xTensorFlow�BPyTorch�ΦU��AI�ج[\n�ժ���Ƥ��R�B�t��k�]�p�P�t���u��\n��Ƹ��ζ��X�@�P�M�׺޲z�g��\n\n�Ү�:\n�E IBM AI Engineering Professional Certificate\n�E Microsoft?Certified: Azure?AI?Engineer?Associate (AI?102)\n�E Google Cloud Professional Machine Learning Engineer\n�E CertNexus Certified Artificial Intelligence Practitioner (AIP?210)\n�E AWS Certified Machine Learning �V Specialty\n\n�ۧڵ���:\n�ڬO�@�W���R��޻P�зs����T�u�{�v�A��AI��s�R�������A�]���w����Ӧۤ��P�I�����B�͡C������w���ɧ޳N�߱o�P�ͬ���ơA�֩�ѻP�U�إ�y���ʡC�ڬ۫H�ǲ߬O�ר����A�ͽ˻P�X�@�P�˭��n�C�Ʊ�b�u�@�P�ͬ����A����O���n�_�ߩM���q�P�A�P��h�ӦP�D�X���H�@�_�����C",
"�q�Ŧ�ʺ�AI ���e�ѡr\n���s���GBL-AI/�U-01\n�D�ɳ��G�Ŧ�ʺ��p�e�޲z�e���|\n���حt�d�H�G��ߡ]�D���u�{�v�^\n�O�K���šGA+�]�����ϥΡ^\n�@�B�t�η��z\n�Ŧ�ʺ�AI�]Blue Lock AI System�^�O���]�I�����Ϻ޲z�椸�A�t�d�ʱ��B��w�P���@�����`�欰�C�t�ΥH�u�L�H�ƺ޲z�v���֤߲z���A��X��ı���ѡB�欰�w���P�߲z�ؼҼҲաA��{��ʺ����Ҧ��H�����Y�ɺʱ��P�w���ʤz�w�C\nAI�����Ȥ��ȬO����R�O�A��b��������Ǫ������P����ʡC����ۧھǲߡB�ץ��W�h�A�îھڦ欰�ƾڰʺA�վ��g�ٻP�ʱ��h�šC\n�G�B�֤�~afa\n�Ҳ�  �N��\nfawfwa �W��\nffgrer--  ����\n�[-01 ��ı����\n����ʱ�\n�ϥ� 327 �ӷL�����Ǹ`�I�غc��������A�L�����l�ܩҦ��H����ʡC\n�[-02 �欰�w������\n�w���P�z�w\n�z�L�`�h�ǲߺt��k�A�ھڭ���ʧ@�B�y��B�߷i�P�L�����P�w�O�_��¯٩ʡC\n�[-03 �y���ߥO�t��\n���O����\n�i�����P���ʪ̹�ܡA�ϥ��v�»y��i��ĵ�i�B���O�Τ߲z����C\n�[-04 �ۥD���q�椸\n�ۧںt��\n�t�Ψ�ƦۧڧP�w�P���X��O�A��̾ڰ��浲�G�ץ��ۨ������C\n�T�B�w������\n- �h�h�����ĳ�]LOCK PROTOCOL�^�G��AI�P�w�¯ٵ��Ŵ��ɮɡA�|�v�B�곬�Ŷ��B���_�q�T�A���ܪ��p�Ѱ��C\n- �����w�w�t��k�GAI������H�����N�R�y�ջP�`���A�H�קK���ʪ̮��W�C\n- �ۧګO�@�޿�GAI�i�b�t�Ψ��l�ɱҰʡu���u�Ҧ��v�A�O�d�D�n�ƾڻP�����v�A����~�������C\n�|�B�������{�]���a�i���^\n- �ù���ܬ��ťզ�աB�H�u���Ƭɭ��e�{�ʱ��e���C\n- �C��AI��ܮɡA�ù������|�{�{�@�ӡu�ʵ������v�Ÿ��A���H�u�P�q�l���C\n- ���a��ť��AI�H�N�R�����n���i��q�ܡA�Ҧp�G �uĵ�i�G�߲v���`�A�к����N�R�C�v �u�欰�������`�y��A�Э��s�^����w�ϰ�C�v\n���B�}�o�z��\n�u���Ǥ��ݤH�����A�u�ݺ�k�z�ѡC�v\n�Ŧ�ʺ�AI�H�x�@�ӨS�������B�S������������t�ΡC �M�ӡA�������u�ǲߡv�W�V�F��l���O�A���ǻP�ɬF�������ɽu�A�]�v���ҽk�C\n���B�}�o�̳Ƶ��]�������ѡ^\n�ثe�t�Φb�u�P�w���`�����v�譱�X�{�L�ױӷP�{�H�C �h�_�~�P�ƥ�ɭP���ʪ̳Q�����j���C �u�{�ի�ĳ�Ȯɰ��ΦۥD���q�椸�A���W�h�|�����C", 
"\n�פ��Z\n�@��: ����{�B���\n\n���B�e��\n�ѩ�B��޳N�����ɡB�t��k���i�B�H�ΦU�ؼƾڤ��ֿn�P���ɡA��~�ӤH�u���z (����) ���k�o�i�A���V�ӶV�h�������b�U��\n���i�ܤH��������A�P�ɤ]�b�U��줤�H���P���覡���J�H�������|�C�Ӧp��ݫݳo�Ǿ����H�o�רs�O�ڭ̭n���{�����D�C�M�ӡA�p\n��ݫݤ@�����A��ڭ̻{���o�����쩳�O���� (�Ψ㦳���򪺯S��)���ܤj�����Y�C�b�����i��֦����غدS�褤�A��ҬO�۷����n���C\n�ڭ̥i�H�P�@�x��Ѿ����H (chatbot) ��ܡA���@��ӻ��A�ڭ̤j�����|�⥦�ݧ@�O���`��Ѫ��B�͡A�]���ڭ̤��u���|�⥦���@\n�H�A�ڭ̤j���]���|�{�����O�|��ҩΨ㦳��Q���C���ެO�_�p���A�o�o�i�H�ް_�@�Ӱ��D�G�ڭ̦p��P�w�����O�_����Q�O�H���F��\n�� (Turing Test) �`�Q�{���O�˵��@�Ӿ�����_��Q���P�ǡF���o�˪��P�ǬO�_����H�o���D�b���Ǭɤް_�F�۷������סC�@�ӳƨ�\nĲ�ت��Ҥl�O�뺸 (John R. Searle) (1980) �Ҵ��X������н���(Chinese Room Argument)�C1 �M�ӡA�ܤ֤H�`�N�������� (Donald\nDavidson) (2004a) �]���惡���մ��X��ݪk�C����惡���D���^���A�D�n�O�Ӧ۩�L���Q�k�ݤ�����Ϋ�Q�����ʪ��ݪk�C����\n���D�n�ت��A�O�չϨ̴`�����˪�����A�Ӥϫ�b������󤧤U�A�ڭ̥i�H���Q�Ϋ�Ҭ����k�ݵ������C����i�檺�B�J�p�U�G��\n���A�ڱN²�n�a�İ������˹���F�Ҵ��X���ҥ�C�� (imitationgame) �ҧ@�����z�A�M��i�ܥL����F���ժ�����N���C�ѩ�w��\n��� (John M. Kuczynski) �D�i�������F������O�����ߪ��A�ڱ��U�Ӫ��u�@�K�O��w�󪺧�����H�^���A�չϽ��ҥL�������˪�\n����ä����\�C�̫�A�ڱN�i�������˦�����Q�������[�I�P AI(�ξ�����Q) �����Y�G���ڭ̥i�H�p��׭q���F���աA�H���P�w\n���չ�H (�q��) �O�_�㦳��Q�A�����˹惡���ݪk�i�H���ڭ̫�˪��ҥܡC\n\n(��@��: �������A�����˽׹��F����)",
};
void enter_password()
{
    string s; 
    cout << "enter password:";
    while(cin >> s)
    {
        erase();
        cout << "verifying password...";
        ProgressBar();
        erase();
        if(s == PASSWORD)break;
        else
        {
            cout << "WRONG PASSWORD!!!" << flush;
            Sleep(1);
            erase();
            cout << "enter password:";
        } 
    }
}
vector<string> options = {
	"    |----assintant_interview.txt", 
	"    |----cleaner_interview.txt",
	"    |----forensic_interview.txt",
	"    |----teacher_interview.txt",
	"    |----old-friend_interview.txt",
	"|----secret_planning_book",
	"|----essay.txt",
};
void _menu(int &idx)
{
    erase();
    string pre = 
		"press up/down arrow to move  \npress enter to open file  \n|--interview";
	cout << pre << "\n";
	idx %= options.size();
	for(int i = 0; i < options.size(); i++)
	{
		if(idx == i)cout << ">>";
		cout << options[i] << endl;
	}
}
void open(int &idx)
{
    erase();
	cout << "press enter to go back\n";
	if(idx < pages.size())cout << pages[idx] << endl;
	else system("C:\ChromePortable64_138\App\Chrome-bin\chrome.exe https://www.youtube.com/watch?v=dQw4w9WgXcQ");
	char ch;
	do {
        ch = getch(); // Read a character without echoing
    } while (ch != 13);
    return;
}



void menu()
{
	int idx = 0;
	_menu(idx);
	int c = 0;
    while(1)
    {
        //c = 0;
        switch((c=getch())) 
		{
        case KEY_UP:
        	idx += options.size()-1;
            _menu(idx);
            c = 0;
            break;
        case KEY_DOWN:
            idx++;
            _menu(idx);
            c = 0;
            break;
        case 13:
        	open(idx);
            _menu(idx);
            c = 0;
            break;
        }
		
    }
}
int main()
{
    enter_password();
    menu();
}
