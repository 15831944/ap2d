--------------------- Standard edition for Daiwa House--------------------------------
--[[

]]--


entry {
	book = { --����Excel�ļ�
		name = [[GSimpleBeam-]],						--�ļ�������ʱ���ã�
		sheets = {										--���ҳ�ļ���
			{											--��һҳ������еڶ�ҳ�����︴�ƣ�
				name = [[GSimpleBeam-]],				--ҳ��ǰ׺
				cell_ws = {								--�����п�
					{
						col = [[A]],
						size = 1.88
					},									--ȱʡ��������ͬ
					{
						col = [[E]],
						size = 5.75,
					},
					{
						col = [[F]],
						size = 1.88,
					},
					{
						col = [[G]],
						size =1.75,
                                         },									--ȱʡ��������ͬ
					{       
						col = [[I]],
						size = 3.63,
					},									--ȱʡ��������ͬ
					{
						col = [[J]],
						size = 1.38,
					},
					{
						col = [[L]],
						size = 1.88
					},
					{
						col = [[M]],
						size =4.5,
                                                
						col = [[N]],
						size =4.88
					},									--ȱʡ��������ͬ
					{
						col = [[O]],
						size = 1.13,
					},
					{
						col = [[P]],
						size = 0.15,
					},
					{
						col = [[Q]],
						size =1.75,
                                         },									--ȱʡ��������ͬ
					{       
						col = [[R]],
						size =1.25,
					},									--ȱʡ��������ͬ
					{
						col = [[S]],
						size = 1.88,
					},
					{
						col = [[U]],
						size = 3
					},
					{
						col = [[V]],
						size =2.75,

                                                col = [[W]],
						size = 3.13
					},									--ȱʡ��������ͬ
					{
						col = [[X]],
						size = 2.25,
					},
					{
						col = [[Z]],
						size = 1.88,
					},
					{
						col = [[AA]],
						size =2.5,
                                         },									--ȱʡ��������ͬ
					{       
						col = [[AD]],
						size = 2.38,
					},									--ȱʡ��������ͬ
					{
						col = [[AE]],
						size = 1.88,
					},
					{
						col = [[AF]],
						size = 2.63
					},
					{
						col = [[AG]],
						size =2.5,
                                                
						col = [[AH]],
						size =5
					},
				},
				cell_hs = {								--�����и�
					{
						id = 1,
						size = 13.5,						--ȱʡ��������ͬ
					},
					{
						id = 3,
						size =14.25,
					},
					{
						id = 4,
						size = 13.5,
					},
					{
						id = 5,
						size = 14.5,
					},
					{
						id = 6,
						size = 13.5,
					},
					{
						id = 8,
						size = 21.75,

                                                id = 9,
						size = 13.5,						--ȱʡ��������ͬ
					},
					{
						id =10,
						size =16.5,
					},
					{
						id = 11,
						size = 13.5,
					},
					{
						id = 12,
						size = 12.75,
					},
					{
						id =22,
						size = 16,
					},
					{
						id = 27,
						size = 21,
					},
				},

--��������ҳ����ʼλ��
--��
--��
				pos_rule = [[
					set_start_x(1);	
					set_start_y(1);	
				]],
				tables = {								--��ļ���
					{									--��һ���������ݣ�
						type = 1,						--������� 1��ʾ�����ɶ����������ݣ� 2��ʾ���ϱ���ļ��ϣ�
						border = 0,						--��ı߽��������趨
						init_rule = [[]],				--�������ݵĳ�ʼ����������Ϊ�գ�
						filter_rule = [[]],				--�������ݵĹ��˹���
						group_rule = [[]],				--�������ݵķ������
						sort_rule = [[]],				--�������ݵ��������
						cells = {						--����еļ���
							{							--��һ��
								content = [[��]],
								content_rule = [[]],
								style = [[����-11]],
								pos_rule = [[set_cell_pos("Z2:AH2");]],
								border = 1,
							},							--�ڶ���
							{
								content = [[�k���� ]],
								content_rule = [[]],
								style = [[����-11]],
								pos_rule = [[set_cell_pos("Z3:AA3");]],
								border = 1,
							},

							{
								content = [[###]],
								content_rule = [[]],
								style = [[����-11]],
								pos_rule = [[set_cell_pos("AB3:AH3");]],
								border = 1,
							},
							{
								content = [[��]],
								content_rule = [[]],
								style = [[����-11]],
								pos_rule = [[set_cell_pos("I5:I5");]],
								border = 0,
							},
							{
								content = [[Ҏ��ץ�`�ȡ��kע��]],
								content_rule = [[]],
								style = [[����-18]],
								pos_rule = [[set_cell_pos("A8:AH8");]],
								border = 0,
							},
							{
								content = [[�kע��]],
								content_rule = [[]],
								style = [[����-12]],
								pos_rule = [[set_cell_pos("X10:AA10");]],
								border = 1,
							},
							{
								content = [[###]],
								content_rule = [[]],
								style = [[����-12]],
								pos_rule = [[set_cell_pos("AB10:AG10");]],
								border = 1,
							},
							{
								content = [[���m��]],
								content_rule = [[]],
								style = [[����-12]],
								pos_rule = [[set_cell_pos("X12:AG12");]],
								border = 1,
							},
							{
								content = [[����:]],
								content_rule = [[]],
								style = [[����-12]],
								pos_rule = [[set_cell_pos("X14:Z14");]],
								border = 1,
							},
							{
								content = [[###]],
								content_rule = [[]],
								style = [[����-12]],
								pos_rule = [[set_cell_pos("AA14:AG14");]],
								border = 1,
							},
							{
								content = [[������:]],
								content_rule = [[]],
								style = [[����-14]],
								pos_rule = [[set_cell_pos("A22:D22");]],
								border = 0,
							},
							{
								content = [[###]],
								content_rule = [[]],
								style = [[����-13]],
								pos_rule = [[set_cell_pos("E22:I23");]],
								border = 1,
							},
							{
								content = [[����]],
								content_rule = [[]],
								style = [[����-14]],
								pos_rule = [[set_cell_pos("J22:M23");]],
								border = 1,
							},
								{
								content = [[###]],
								content_rule = [[]],
								style = [[����-12]],
								pos_rule = [[set_cell_pos("N22:R23");]],
								border = 1,
							},
								{
								content = [[�����λ]],
								content_rule = [[]],
								style = [[����-11]],
								pos_rule = [[set_cell_pos("S22:U22");]],
								border = 1,
							},
							{
								content = [[��]],
								content_rule = [[]],
								style = [[����-11]],
								pos_rule = [[set_cell_pos("S23:U23");]],
								border = 1,
							},
							{
								content = [[ϣ���{��]],
								content_rule = [[]],
								style = [[����-11]],
								pos_rule = [[set_cell_pos("V22:X23");]],
								border = 1,
							},
							{
								content = [[��ƽ��  ����  ��  ��],
								content_rule = [[]],
								style = [[����-11]],
								pos_rule = [[set_cell_pos("Z22:AH23");]],
								border = 1,
							},
							{
								content = [[�{�����롡����]],
								content_rule = [[]],
								style = [[����-12]],
								pos_rule = [[set_cell_pos("A24:E24");]],
								border = 1,
							},
							{
								content = [[��]],
								content_rule = [[]],
								style = [[����-12]],
								pos_rule = [[set_cell_pos("F24:I24");]],
								border = 1,
							},
								{
								content = [[��]],
								content_rule = [[]],
								style = [[����-12]],
								pos_rule = [[set_cell_pos("J24:M24");]],
								border = 1,
							},
								{
								content = [[��]],
								content_rule = [[]],
								style = [[����-12]],
								pos_rule = [[set_cell_pos("N24:Q24");]],
								border = 1,
							},
							{
								content = [[��]],
								content_rule = [[]],
								style = [[����-12]],
								pos_rule = [[set_cell_pos("R24:U24");]],
								border = 1,
							},
							{
								content = [[��]],
								content_rule = [[]],
								style = [[����-12]],
								pos_rule = [[set_cell_pos("V24:X24");]],
								border = 1,
							},
							{
								content = [[��]],
								content_rule = [[]],
								style = [[����-12]],
								pos_rule = [[set_cell_pos("Z24:AB24");]],
								border = 1,
							},
							{
								content = [[��]],
								content_rule = [[]],
								style = [[����-12]],
								pos_rule = [[set_cell_pos("AD24:AF24");]],
								border = 1,
							},
							{
								content = [[��]],
								content_rule = [[]],
								style = [[����-12]],
								pos_rule = [[set_cell_pos("AG24:AH24");]],
								border = 1,
							},
							{
								content = [[��������������]],
								content_rule = [[]],
								style = [[����-12]],
								pos_rule = [[set_cell_pos("A25:E25");]],
								border = 1,
							},
							{
							content = [[�ӹ�����ӛ��]],
								content_rule = [[]],
								style = [[����-12]],
								pos_rule = [[set_cell_pos("A26:E26");]],
								border = 1,
							},
							{
								content = [[Ҏ����ӛ����]],
								content_rule = [[]],
								style = [[����-12]],
								pos_rule = [[set_cell_pos("A27:J27");]],
								border = 1,
							},
							{
								content = [[�g��]],
								content_rule = [[]],
								style = [[����-12]],
								pos_rule = [[set_cell_pos("L27:Q27");]],
								border = 1,
							},

							{
								content = [[����]],
								content_rule = [[]],
								style = [[����-12]],
								pos_rule = [[set_cell_pos("R27:V27");]],
								border = 1,
							},
							{
								content = [[�t��],
								content_rule = [[]],
								style = [[����-12]],
								pos_rule = [[set_cell_pos("W27:AA27");]],
								border = 1,
							},
							{
								content = [[�䡡������]],
								content_rule = [[]],
								style = [[����-12]],
								pos_rule = [[set_cell_pos("AB27:AH27");]],
								border = 1,
							},
							{
								content = [[###]],
								content_rule = [[]],
								style = [[����-12]],
								pos_rule = [[set_cell_pos("A28:J28");]],
								border = 1,
							},
							{
								content = [[###]],
								content_rule = [[]],
								style = [[����-12]],
								pos_rule = [[set_cell_pos("L28:Q28");]],
								border = 1,
							},
							{
								content = [[###]],
								content_rule = [[]],
								style = [[����-12]],
								pos_rule = [[set_cell_pos("R28:V28");]],
								border = 1,
							},
							{
								content = [[###]],
								content_rule = [[]],
								style = [[����-12]],
								pos_rule = [[set_cell_pos("W28:AA28");]],
								border = 1,
							},
							{
								 
							},

						},
					},
				},
			},
		},
		style_db = {									--�����ļ�����ʽ��
			css = {										--��ʽ�ļ���
				{										--��һ����ʽ
					type = 0,							--����
					name = [[����-14]],					--��ʽ��
					font = [[�ͣ� ����]],				--��ʽ����
					text_color = 1,						--������ɫ
					back_color = 0,						--������ɫ
					size = 14,							--�ֺ�
					blod = 0,							--�Ӵ�
					italic = 0,							--б����
					h_align = 3,						--ˮƽ����
					v_align = 2,						--��ֱ����
				},
				{
					type = 0,
					name = [[����-12]],
					font = [[�ͣ� ����]],
					text_color = 1,
					back_color = 0,
					size = 12,
					blod = 0,
					italic = 0,
					h_align = 3,
					v_align = 3,
				},
				{
					type = 0,
					name = [[����-10]],
					font = [[�ͣ� ����]],
					text_color = 1,
					back_color = 0,
					size = 10,
					blod = 0,
					italic = 0,
					h_align = 3,
					v_align = 2,
				},
				{
					type = 0,
					name = [[����-9]],
					font = [[�ͣ� ����]],
					text_color = 1,
					back_color = 0,
					size = 9,
					blod = 0,
					italic = 0,
					h_align = 3,
					v_align = 2,
				},
				{
					type = 0,
					name = [[����-8]],
					font = [[�ͣ� ����]],
					text_color = 1,
					back_color = 0,
					size = 8,
					blod = 0,
					italic = 0,
					h_align = 3,
					v_align = 2,
				},
				{
					type = 0,
					name = [[����-7]],
					font = [[�ͣ� ����]],
					text_color = 1,
					back_color = 0,
					size = 7,
					blod = 0,
					italic = 0,
					h_align = 3,
					v_align = 2,
				},
			},
		},
	},
}

