DELETE FROM ai_playerbot_texts WHERE name IN (
    'class_role_twin_emperors_veklor_side_warlock_tank',
    'class_role_twin_emperors_veknilash_side_warlock_tank'
);

DELETE FROM ai_playerbot_texts_chance WHERE name IN (
    'class_role_twin_emperors_veklor_side_warlock_tank',
    'class_role_twin_emperors_veknilash_side_warlock_tank'
);

INSERT INTO ai_playerbot_texts
    (id, name, text, say_type, reply_type, text_loc1, text_loc2, text_loc3, text_loc4, text_loc5, text_loc6, text_loc7, text_loc8)
VALUES
    (1945, 'class_role_twin_emperors_veklor_side_warlock_tank', 'Twin Emperors warlock tank, Vek''lor''s side', 0, 0, '쌍둥이 황제 흑마법사 탱커 (베클로어 쪽)', 'tank démoniste des Empereurs jumeaux, côté Vek''lor', 'Zwillingsimperatoren-Hexenmeistertank, Seite von Vek''lor', '双子皇帝术士坦克（维克洛尔一侧）', '雙子皇帝術士坦克（維克洛爾一側）', 'tanque brujo de los Emperadores gemelos, lado de Vek''lor', 'tanque brujo de los Emperadores gemelos, lado de Vek''lor', 'Танк-чернокнижник для Императоров-близнецов (сторона Век''лора)');

INSERT INTO ai_playerbot_texts
    (id, name, text, say_type, reply_type, text_loc1, text_loc2, text_loc3, text_loc4, text_loc5, text_loc6, text_loc7, text_loc8)
VALUES
    (1946, 'class_role_twin_emperors_veknilash_side_warlock_tank', 'Twin Emperors warlock tank, Vek''nilash''s side', 0, 0, '쌍둥이 황제 흑마법사 탱커 (베크닐라쉬 쪽)', 'tank démoniste des Empereurs jumeaux, côté Vek''nilash', 'Zwillingsimperatoren-Hexenmeistertank, Seite von Vek''nilash', '双子皇帝术士坦克（维克尼拉斯一侧）', '雙子皇帝術士坦克（維克尼拉斯一側）', 'tanque brujo de los Emperadores gemelos, lado de Vek''nilash', 'tanque brujo de los Emperadores gemelos, lado de Vek''nilash', 'Танк-чернокнижник для Императоров-близнецов (сторона Век''нилаша)');

INSERT INTO ai_playerbot_texts_chance (name, probability) VALUES
    ('class_role_twin_emperors_veklor_side_warlock_tank', 100),
    ('class_role_twin_emperors_veknilash_side_warlock_tank', 100);
