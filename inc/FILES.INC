{ Prints dungeon map to external file }
//[psect(misc2$code)]
procedure print_map;
	var
	i1,
	i2,
	i3,
	i4,
	i5,
	i6,
	i7,
	i8: Integer;
	dun_line: string[133];
	filename1: string[80];
	tmp: AnsiChar;
	clr: AnsiChar;
	file1: Text;

	begin
	prt('File name: ', 1, 1);
	if (get_string(filename1, 1, 12, 64)) then
		begin
		if (length(filename1) = 0) then
			filename1:= 'MORIAMAP.DAT';
//		open(file1, filename1, error:= continue);
		AssignFile(file1, string(filename1));
		Rewrite(file1);
//		if (status(file1) = 0) then
		if IOResult <> 0 then
			begin
			prt('Writing moria dungeon map...', 1, 1);
			put_qio;
//			Rewrite(file1, error:= continue);
			i1:= 1;
			i7:= 0;
			repeat
				i2:= 1;
				i3:= i1 + outpage_height - 1;
				if (i3 > cur_height) then
					i3:= cur_height;
				i7    := i7 + 1;
				i8    := 0;
				repeat
					i4:= i2 + outpage_width - 1;
					if (i4 > cur_width) then
						i4:= cur_width;
					i8    := i8 + 1;
//					writeln(file1, chr(12), error:= continue);
					writeln(file1, chr(12));
//					write(file1, 'Section[', i7: 1, ',', i8: 1, '];     ',
//						error:= continue);
					write(file1, 'Section[', i7: 1, ',', i8: 1, '];     ');
//					writeln(file1, 'Depth : ', (dun_level * 50): 1, ' (feet)',
//						error:= continue);
					writeln(file1, 'Depth : ', (dun_level * 50): 1, ' (feet)');
//					writeln(file1, ' ', error:= continue);
					writeln(file1, ' ');
//					write(file1, '   ', error:= continue);
					write(file1, '   ');
					for i5:= i2 to i4 do
						begin
						i6:= (i5 div 100);
//						write(file1, i6:1, error:= continue);
						write(file1, i6:1);
						end;
//					writeln(file1, error:= continue);
					writeln(file1);
//					write(file1, '   ', error:= continue);
					write(file1, '   ');
					for i5:= i2 to i4 do
						begin
						i6:= (i5 div 10) - (i5 div 100) * 10;
//						write(file1, i6:1, error:= continue);
						write(file1, i6:1);
						end;
//					writeln(file1, error:= continue);
					writeln(file1);
//					write(file1, '   ', error:= continue);
					write(file1, '   ');
					for i5:= i2 to i4 do
						begin
						i6:= i5 - (i5 div 10) * 10;
//						write(file1, i6:1, error:= continue);
						write(file1, i6:1);
						end;
//					writeln(file1, error:= continue);
					writeln(file1);
					for i5:= i1 to i3 do
						begin
//						writev(dun_line, i5: 3);
						dun_line:= PadLeft(AnsiString(IntToStr(i5)), 3);
						for i6:= i2 to i4 do
							begin
							if (test_light(i5, i6)) then
								loc_symbol(i5, i6, tmp, clr)
							else
								tmp := ' ';
							dun_line:= dun_line + tmp;
							end;
//						writeln(file1, dun_line, error:= continue);
						writeln(file1, dun_line);
						end;

					i2:= i2 + outpage_width;
					until (i2 >= cur_width);

				i1:= i1 + outpage_height;
				until (i1 >= cur_height);

//			close(file1, error:= continue);
			CloseFile(file1);
			prt('Completed.', 1, 1);
			end;
		end
	end;


{ Prints a list of random objects to a file.  Note that the object file
  is a sampling of objects which would be expected to appear on that level. }
//[psect(misc2$code)]
procedure print_objects;
	var
	nobj,
	i1,
	i2,
	level: Integer;
	filename1,
	tmp_str: AnsiString;
	file1: Text;

	begin
	prt('Produce objects on what level?: ', 1, 1);
	get_string(tmp_str, 1, 33, 10);

//	level:= 0;
//	readv(tmp_str, level, error:= continue);
	if not TryStrToInt(string(tmp_str), level) then
		level:= 0;

	prt('Produce how many objects?: ', 1, 1);
	get_string(tmp_str, 1, 28, 10);

//	nobj:= 0;
//	readv(tmp_str, nobj, error:= continue);
	if not TryStrToInt(string(tmp_str), nobj) then
		nobj:= 0;

	if ((nobj > 0) and (level > -1) and (level < 1201)) then
		begin
		if (nobj > 9999) then
			nobj:= 9999;
		prt('File name: ', 1, 1);
		if (get_string(filename1, 1, 12, 64)) then
			begin
			if (length(filename1) = 0) then
				filename1:= 'MORIAOBJ.DAT';

//			open(file1, filename1, error:= continue);
			AssignFile(file1, string(filename1));
			Rewrite(file1);
			if (IOResult = 0) then
				begin
//				writev(tmp_str, nobj: 1);
				tmp_str:= AnsiString(IntToStr(nobj));
				prt(tmp_str + ' Random objects being produced...', 1, 1);
				put_qio;
//				Rewrite(file1, error:= continue);
//				writeln(file1, '*** Random object sampling:', error:= continue);
				writeln(file1, '*** Random object sampling:');
//				writeln(file1, '*** ', nobj:1, ' objects', error:= continue);
				writeln(file1, '*** ', nobj:1, ' objects');
//				writeln(file1, '*** For level ', level:1, error:= continue);
				writeln(file1, '*** For level ', level:1);
//				writeln(file1, '', error:= continue);
				writeln(file1, '');
//				writeln(file1, '', error:= continue);
				writeln(file1, '');
				popt(i2);
				for i1:= 1 to nobj do
					begin
					t_list[i2]:= object_list[get_obj_num(level)];
					magic_treasure(i2, level);
					invenTemp:= t_list[i2];
					with invenTemp do
						begin
						unquote(name);
						known1(name);
						known2(name);
						end;
					objdes(tmp_str, @invenTemp, true);
//					writeln(file1, tmp_str, error:= continue);
					writeln(file1, tmp_str);
					end;
				pusht(i2);
//				close(file1, error:= continue);
				CloseFile(file1);
				prt('Completed.', 1, 1);
				end
			else
				prt('File could not be opened.', 1, 1);
			end;
		end;
	end;


{ Prints a listing of monsters }
//[psect(wizard$code)]
procedure print_monsters;
	var
	i1, i2, xpos, atype, adesc: Integer;
	file1:                      Text;
	out_val, filename1:         vtype;
	attstr, attx:               vtype;
	damstr:                     AnsiString;

	begin
	prt('File name: ', 1, 1);
	if (get_string(filename1, 1, 12, 64)) then
		begin
		if (length(filename1) = 0) then
			filename1:= 'MORIAMON.DAT';
//		open(file1, filename1, error:= continue);
		AssignFile(file1, string(filename1));
		Rewrite(file1);
		if (IOResult = 0) then
			begin
			prt('Writing monster dictionary...', 1, 1);
			put_qio;
//			Rewrite(file1, error:= continue);
			for i1:= 1 to max_creatures do
				with c_list[i1] do
					begin
{ BEGIN writing to file }
//					writeln(file1,
//						'--------------------------------------------',
//						error:= continue);
					writeln(file1, '--------------------------------------------');
					out_val:= name + '                              ';
//					writeln(file1, i1:3, '  ', out_val:30, '     (', cchar:1,
//							')', error:= continue);
					writeln(file1, i1:3, '  ', out_val:30, '     (', cchar:1, ')');
//					writeln(file1, '     Speed =', speed:2, '  Level     =',
//							level:2, '  Exp =', mexp:5, error:= continue);
					writeln(file1, '     Speed =', speed:2, '  Level     =',
							level:2, '  Exp =', mexp:5);
//					writeln(file1, '     AC    =', ac:2, '  Eye-sight =', aaf:2,
//							'  HD  =', hd:5, error:= continue);
					writeln(file1, '     AC    =', ac:2, '  Eye-sight =', aaf:2,
							'  HD  =', hd:5);
					if (($80000000 and cmove) <> 0) then
//						writeln(file1, '     Creature is a ***Win Creature***',
//								error:= continue);
						writeln(file1, '     Creature is a ***Win Creature***');
					if (($00080000 and cmove) <> 0) then
//						writeln(file1,
//								'     Creature Eats/kills other creatures.',
//								error:= continue);
						writeln(file1, '     Creature eats/kills other creatures.');
					if (($0001 and cdefense) <> 0) then
//						writeln(file1, '     Creature is a dragon.',
//								error:= continue);
						writeln(file1, '     Creature is a dragon.');
					if (($0002 and cdefense) <> 0) then
//						writeln(file1, '     Creature is a monster.',
//								error:= continue);
						writeln(file1, '     Creature is a monster.');
					if (($0004 and cdefense) <> 0) then
//						writeln(file1, '     Creature is evil.',
//								error:= continue);
						writeln(file1, '     Creature is evil.');
					if (($0008 and cdefense) <> 0) then
//						writeln(file1, '     Creature is undead.',
//								error:= continue);
						writeln(file1, '     Creature is undead.');
					if (($0010 and cdefense) <> 0) then
//						writeln(file1, '     Creature harmed by cold.',
//								error:= continue);
						writeln(file1, '     Creature harmed by cold.');
					if (($0020 and cdefense) <> 0) then
//						writeln(file1, '     Creature harmed by fire.',
//								error:= continue);
						writeln(file1, '     Creature harmed by fire.');
					if (($0040 and cdefense) <> 0) then
//						writeln(file1, '     Creature harmed by poison.',
//								error:= continue);
						writeln(file1, '     Creature harmed by poison.');
					if (($0080 and cdefense) <> 0) then
//						writeln(file1, '     Creature harmed by acid.',
//								error:= continue);
						writeln(file1, '     Creature harmed by acid.');
					if (($0100 and cdefense) <> 0) then
//						writeln(file1, '     Creature harmed by blue light.',
//								error:= continue);
						writeln(file1, '     Creature harmed by blue light.');
					if (($0200 and cdefense) <> 0) then
//						writeln(file1, '     Creature harmed by Stone-to-Mud.',
//								error:= continue);
						writeln(file1, '     Creature harmed by Stone-to-Mud.');
					if (($0400 and cdefense) <> 0) then
						writeln(file1, '     Player loses experience if harms.');
					if (($1000 and cdefense) <> 0) then
//						writeln(file1,
//								'     Creature cannot be charmed or slept.',
//								error:= continue);
						writeln(file1, '     Creature cannot be charmed or slept.');
					if (($2000 and cdefense) <> 0) then
//						writeln(file1, '     Creature seen with Infra-Vision.',
//								error:= continue);
						writeln(file1, '     Creature seen with Infra-Vision.');
					if (($4000 and cdefense) <> 0) then
//						writeln(file1, '     Creature has MAX hit points.',
//								error:= continue);
						writeln(file1, '     Creature has MAX hit points.');
					if (($00010000 and cmove) <> 0) then
//						writeln(file1, '     Creature is invisible.',
//								error:= continue);
						writeln(file1, '     Creature is invisible.');
					if (($00100000 and cmove) <> 0) then
//						writeln(file1, '     Creature picks up objects.',
//								error:= continue);
						writeln(file1, '     Creature picks up objects.');
					if (($00200000 and cmove) <> 0) then
//						writeln(file1, '     Creature multiplies.',
//								error:= continue);
						writeln(file1, '     Creature multiplies.');
					if (($01000000 and cmove) <> 0) then
//						writeln(file1, '     Carries object(s).',
//								error:= continue);
						writeln(file1, '     Carries object(s).');
					if (($02000000 and cmove) <> 0) then
//						writeln(file1, '     Carries gold, gems, ect.',
//								error:= continue);
						writeln(file1, '     Carries gold, gems, ect.');
					if (($04000000 and cmove) <> 0) then
//						writeln(file1, '       Has object/gold 60% of time.',
//								error:= continue);
						writeln(file1, '       Has object/gold 60% of time.');
					if (($08000000 and cmove) <> 0) then
//						writeln(file1, '       Has object/gold 90% of time.',
//								error:= continue);
						writeln(file1, '       Has object/gold 90% of time.');
					if (($10000000 and cmove) <> 0) then
//						writeln(file1, '       Has 1d2 object(s)/gold.',
//								error:= continue);
						writeln(file1, '       Has 1d2 object(s)/gold.');
					if (($20000000 and cmove) <> 0) then
//						writeln(file1, '       Has 2d2 object(s)/gold.',
//								error:= continue);
						writeln(file1, '       Has 2d2 object(s)/gold.');
					if (($40000000 and cmove) <> 0) then
//						writeln(file1, '       Has 4d2 object(s)/gold.',
//								error:= continue);
						writeln(file1, '       Has 4d2 object(s)/gold.');

{ Creature casts spells / Breathes Dragon breath. }
//dengland   All of these Writelns had error:= continue.  I'm just going to
//		remove them to save time.
					if (spells > 0) then
						begin
						writeln(file1, '   --Spells/Dragon Breath =');
						writeln(file1, '       Casts spells 1 out of ',
							($F and spells):1, ' turns.');
						if (($00000010 and spells) <> 0) then
							writeln(file1, '       Can teleport short.');
						if (($00000020 and spells) <> 0) then
							writeln(file1, '       Can teleport long.');
						if (($00000040 and spells) <> 0) then
							writeln(file1, '       Teleport player to itself.');
						if (($00000080 and spells) <> 0) then
							writeln(file1, '       Cause light wounds.');
						if (($00000100 and spells) <> 0) then
							writeln(file1, '       Cause serious wounds.');
						if (($00000200 and spells) <> 0) then
							writeln(file1, '       Hold person.');
						if (($00000400 and spells) <> 0) then
							writeln(file1, '       Cause blindness.');
						if (($00000800 and spells) <> 0) then
							writeln(file1, '       Cause confusion.');
						if (($00001000 and spells) <> 0) then
							writeln(file1, '       Cause fear.');
						if (($00002000 and spells) <> 0) then
							writeln(file1, '       Summon a monster.');
						if (($00004000 and spells) <> 0) then
							writeln(file1, '       Summon an undead.');
						if (($00008000 and spells) <> 0) then
							writeln(file1, '       Slow person.');
						if (($00010000 and spells) <> 0) then
							writeln(file1, '       Drains mana for healing.');
						if (($00020000 and spells) <> 0) then
							writeln(file1, '       **Unknown spell value**');
						if (($00040000 and spells) <> 0) then
							writeln(file1, '       **Unknown spell value**');
						if (($00080000 and spells) <> 0) then
							writeln(file1,
								'       Breathes Lightning Dragon Breath.');
						if (($00100000 and spells) <> 0) then
							writeln(file1, '       Breathes Gas Dragon Breath.');
						if (($00200000 and spells) <> 0) then
							writeln(file1, '       Breathes Acid Dragon Breath.');
						if (($00400000 and spells) <> 0) then
							writeln(file1, '       Breathes Frost Dragon Breath.');
						if (($00800000 and spells) <> 0) then
							writeln(file1, '       Breathes Fire Dragon Breath.');
						end;

{ Movement for creature }
					writeln(file1, '   --Movement =');
					if (($00000001 and cmove) <> 0) then
						writeln(file1, '       Move only to attack.');
					if (($00000002 and cmove) <> 0) then
						writeln(file1, '       Move and attack normally.');
					if (($00000008 and cmove) <> 0) then
						writeln(file1, '       20% random movement.');
					if (($00000010 and cmove) <> 0) then
						writeln(file1, '       40% random movement.');
					if (($00000020 and cmove) <> 0) then
						writeln(file1, '       75% random movement.');
					if (($00020000 and cmove) <> 0) then
						writeln(file1, '       Can open doors.');
					if (($00040000 and cmove) <> 0) then
						writeln(file1, '       Can phase through walls.');
					writeln(file1, '   --Creature attacks =');
					attstr:= damage;
					while (length(attstr) > 0) do
						begin
						xpos:= index(attstr, '|');
						if (xpos > 0) then
							begin
//							attx  := substr(attstr, 1, xpos - 1);
							attx  := Copy(attstr, 1, xpos - 1);
//							attstr:= substr(attstr, xpos + 1, length(attstr) - xpos);
							attstr:= Copy(attstr, xpos + 1, length(attstr) - xpos);
							end
						else
							begin
							attx  := attstr;
							attstr:= '';
							end;

//						readv(attx, atype, adesc, damstr);
						sscanf(attx, '%d%d%s', [@atype, @adesc, @damstr]);

						out_val:= '';
						case adesc of
							1:
								out_val:= '       Hits for ';
							2:
								out_val:= '       Bites for ';
							3:
								out_val:= '       Claws for ';
							4:
								out_val:= '       Stings for ';
							5:
								out_val:= '       Touches for ';
							6:
								out_val:= '       Kicks for ';
							7:
								out_val:= '       Gazes for ';
							8:
								out_val:= '       Breathes for ';
							9:
								out_val:= '       Spits for ';
							10:
								out_val:= '       Wails for ';
							11:
								out_val:= '       Embraces for ';
							12:
								out_val:= '       Crawls on you for ';
							13:
								out_val:= '       Shoots spores for ';
							14:
								out_val:= '       Begs for money for ';
							15:
								out_val:= '       Slimes you for ';
							16:
								out_val:= '       Crushes you for ';
							17:
								out_val:= '       Tramples you for ';
							18:
								out_val:= '       Drools on you for ';
							19:
								out_val:= '       "Iggy attacks" you for ';
							20:
								out_val:= '       Touches you with its tentacles for ';
							99:
								out_val:= '       Is repelled...';
							else out_val:= '     **Unknown description** ';

							end;

						case atype of
							{ Normal attack }
							1:
								out_val:= out_val + 'normal damage.';
							{ Poison Strength }
							2:
								out_val:= out_val + 'lowering strength.';
							{ Confusion attack }
							3:
								out_val:= out_val + 'confusion.';
							{ Fear attack }
							4:
								out_val:= out_val + 'fear.';
							{ Fire attack }
							5:
								out_val:= out_val + 'fire damage.';
							{ Acid attack }
							6:
								out_val:= out_val + 'acid damage.';
							{ Cold attack }
							7:
								out_val:= out_val + 'cold damage.';
							{ Lightning attack }
							8:
								out_val:= out_val + 'lightning damage.';
							{ Corrosion attack }
							9:
								out_val:= out_val + 'corrosion damage.';
							{ Blindness attack }
							10:
								out_val:= out_val + 'blindness.';
							{ Paralysis attack }
							11:
								out_val:= out_val + 'paralyzation.';
							{ Steal Money }
							12:
								out_val:= out_val + 'stealing money.';
							{ Steal Object }
							13:
								out_val:= out_val + 'stealing object.';
							{ Poison }
							14:
								out_val:= out_val + 'poison damage.';
							{ Lose Dex }
							15:
								out_val:= out_val + 'lose dexterity.';
							{ Lose Con }
							16:
								out_val:= out_val + 'lose constitution.';
							{ Lose Int }
							17:
								out_val:= out_val + 'lose intelligence.';
							{ Lose Wis }
							18:
								out_val:= out_val + 'lose wisdom.';
							{ Lose Exp }
							19:
								out_val:= out_val + 'lose experience.';
							{ Aggravation }
							20:
								out_val:= out_val + 'aggravates monsters.';
							{ Disenchant }
							21:
								out_val:= out_val + 'disenchants objects.';
							{ Eats food }
							22:
								out_val:= out_val + 'eating food.';
							{ Eats light }
							23:
								out_val:= out_val + 'eating light source.';
							{ Eats charges }
							24:
								out_val:= out_val + 'absorbing charges.';
							{ Vampire Bite }
							25:
								out_val:= out_val +
										'losing strength and experience';
							{ Turn to Stone }
							26:
								out_val:= out_val + 'turning to stone.';
							{ Mind Flayer }
							27:
								out_val:= out_val + 'sucking your brain out.';
							{ Hell Horse }
							28:
								out_val:= out_val + 'NightMare blindness.';
							{ Vargouille }
							29:
								out_val:= out_val + 'draining max hit points.';
							{ Special }
							99:
								out_val      := out_val + 'blank message.';
							else
								out_val:= out_val + '**Unknown value**';
							end;

						out_val:= out_val + ' (' + damstr + ')';
						writeln(file1, out_val);
						end;

					for i2:= 1 to 2 do
						writeln(file1, ' ');
					end;

{ end writing to file }
//			close(file1, error:= continue);
			CloseFile(file1);
			prt('Completed.', 1, 1);
			end;
		end
	end;


{ Print the character to a file or device }
//[psect(misc2$code)]
procedure file_character;
	var
	i1, i2, xbth, xbthb, xfos, xsrh, xstl, xdis, xsave, xdev: Integer;
	xinfra: VType;
	file1: Text;
	out_val, filename1, prt1, prt2, new_page: AnsiString;
	out_str, out_int, out_wis, out_dex, out_con, out_chr: Stat_Type;
	t: TMoriaInvenType;

	begin
	prt('File name: ', 1, 1);
	if (get_string(filename1, 1, 12, 64)) then
		begin
		if (length(filename1) = 0) then
			filename1:= 'MORIACHR.DAT';

//		open(file1, filename1, error:= continue);
		AssignFile(file1, string(filename1));
		Rewrite(file1);

		if (IOResult = 0) then
			begin
			prt('Writing character sheet...', 1, 1);
			put_qio;
//			Rewrite(file1, error:= continue);
			new_page:= chr(12);
			writeln(file1, new_page);
			cnv_stat(py.stat.cstr, out_str);
			cnv_stat(py.stat.cint, out_int);
			cnv_stat(py.stat.cwis, out_wis);
			cnv_stat(py.stat.cdex, out_dex);
			cnv_stat(py.stat.ccon, out_con);
			cnv_stat(py.stat.cchr, out_chr);
			writeln(file1, ' ');
			writeln(file1, ' ');
			writeln(file1, ' ');
			write(file1, '  Name  :', PadRight(py.misc.name, 25));
			write(file1, '  Age         :', py.misc.age:4);
			writeln(file1, '     Strength     :', out_str:6);
			write(file1, '  Race  :', PadRight(py.misc.race, 25));
			write(file1, '  Height      :', py.misc.ht:4);
			writeln(file1, '     Intelligence :', out_int:6);
			write(file1, '  Sex   :', PadRight(py.misc.sex, 25));
			write(file1, '  Weight      :', py.misc.wt:4);
			writeln(file1, '     Wisdom       :', out_wis:6);
			write(file1, '  Class :', PadRight(py.misc.tclass, 25));
			write(file1, '  Social class:', py.misc.sc:4);
			writeln(file1, '     Dexterity    :', out_dex:6);
			write(file1, '  Title :', PadRight(py.misc.title, 25));
			write(file1, '               ', '    ');
			writeln(file1, '     Constitution :', out_con:6);
			write(file1, '         ', ' ':30);
			write(file1, '              ');
			writeln(file1, '     Charisma     :', out_chr:6);
			writeln(file1, ' ');
			writeln(file1, ' ');
			writeln(file1, ' ');
			writeln(file1, ' ');
			write(file1, '  + To hit    :', py.misc.dis_th:6);
			write(file1, '     Level      :', py.misc.lev:6);
			writeln(file1, '     Max hit points :', py.misc.mhp:6);
			write(file1, '  + To damage :', py.misc.dis_td:6);
			write(file1, '     Experience :', py.misc.exp:6);
			writeln(file1, '     Cur hit points :', trunc(py.misc.chp):6);
			write(file1, '  + To AC     :', py.misc.dis_tac:6);
			write(file1, '     Gold       :', py.misc.au:6);
			writeln(file1, '     Max mana       :', py.misc.mana:6);
			write(file1, '    Total AC  :', py.misc.dis_ac:6);
			write(file1, '                       ');
			writeln(file1, '     Current mana   :', py.misc.mana:6);

			writeln(file1, ' ');
			writeln(file1, ' ');
			with py.misc do
				begin
				xbth := bth + lev * bth_lev_adj + ptohit * bth_plus_adj;
				xbthb:= bthb + lev * bth_lev_adj + ptohit * bth_plus_adj;
				xfos := 27 - fos;
				if (xfos < 0) then
					xfos:= 0;
				xsrh    := srh + int_adj;
				xstl    := stl;
				xdis    := disarm + lev + 2 * todis_adj + int_adj;
				xsave   := save + lev + wis_adj;
				xdev    := save + lev + int_adj;

//				writev(xinfra, py.flags.see_infra * 10: 1, ' feet');
				xinfra:= ShortString(IntToStr(py.flags.see_infra * 10) + ' feet');
				end;
			writeln(file1, '(Miscellaneous Abilities)':40);
			writeln(file1, ' ');
			write(file1, '  Fighting    : ', PadRight(likert(xbth, 12), 10));
			write(file1, '  Stealth     : ', PadRight(likert(xstl, 1), 10));
			writeln(file1, '  Perception  : ', PadRight(likert(xfos, 3), 10));
			write(file1, '  Throw/Bows  : ', PadRight(likert(xbthb, 12), 10));
			write(file1, '  Disarming   : ', PadRight(likert(xdis, 8), 10));
			writeln(file1, '  Searching   : ', PadRight(likert(xsrh, 6), 10));
			write(file1, '  Saving Throw: ', PadRight(likert(xsave, 6), 10));
			write(file1, '  Magic Device: ', PadRight(likert(xdev, 7), 10));
			writeln(file1, '  Infra-Vision: ', PadRight(xinfra, 10));
{ Write out the character's history }
			writeln(file1, ' ');
			writeln(file1, ' ');
			writeln(file1, 'Character Background':45);
			for i1:= 1 to 5 do
				writeln(file1, PadRight(py.misc.history[i1], 71):76);
{ Write out the equipment list. }
			i2:= 0;
			writeln(file1, ' ');
			writeln(file1, ' ');
			writeln(file1, '  [Character''s equipment list]');
			writeln(file1, ' ');
//			if (equip_ctr = 0) then
//				writeln(file1, '  Character has no equipment in use.')
//			else
				for i1:= Ord(Low(TMoriaInvenWear)) to Ord(High(TMoriaInvenWear)) do
					with newInventory[mitWornWielding, i1] do
						if (tval > 0) then
							begin
							case i1 of
								23:
									prt1:= ') You are wielding   : ';
								24:
									prt1:= ') Worn on head       : ';
								25:
									prt1:= ') Worn around neck   : ';
								26:
									prt1:= ') Worn on body       : ';
								27:
									prt1:= ') Worn on shield arm : ';
								28:
									prt1:= ') Worn on hands      : ';
								29:
									prt1:= ') Right ring finger  : ';
								30:
									prt1:= ') Left  ring finger  : ';
								31:
									prt1:= ') Worn on feet       : ';
								32:
									prt1:= ') Worn about body    : ';
								33:
									prt1:= ') Light source is    : ';
								34:
									prt1:= ') Secondary weapon   : ';
								else
									prt1:= ') *Unknown value*    : ';
								end;
							i2:= i2 + 1;
							objdes(prt2, @(newInventory[mitWornWielding, i1]), true);
//							writev(out_val, '  ', chr(i2 + 96), prt1, prt2);
							out_val:= AnsiString('  ' + Chr(i2 + 96) + string(prt1) + string(prt2));
							writeln(file1, out_val);
							end;

{ Write out the character's inventory. }
			writeln(file1, new_page);
			writeln(file1, ' ');
			writeln(file1, ' ');
			writeln(file1, ' ');
			writeln(file1, '  [General inventory list]');
			writeln(file1, ' ');
			if (inven_ctr = 0) then
				writeln(file1, '  Character has no objects in inventory.')
			else
				begin
				for t:= Low(TMoriaInvenType) to Pred(High(TMoriaInvenType)) do
					for i1:= 0 to Length(newInventory[t]) - 1 do
						begin
						objdes(prt1, @newInventory[t, i1], true);
//						writev(out_val, chr(i1 + 96), ') ', prt1);
//						out_val:= AnsiString(chr(i1 + 96) + ') ' + string(prt1));
						out_val:= prt1;
						writeln(file1, out_val);
						end
				end;
			writeln(file1, new_page);
//			close(file1, error:= continue);
			CloseFile(file1);
			prt('Completed.', 1, 1);
			end;
		end
	end;


