// source file: prog/sqlite.cj
import '../sys/cj.js'
/* 1  */	import * as sqlite from 'https://deno.land/x/sqlite/mod.ts';
/* 4  */	let db=new sqlite.DB('test.db');
/* 5  */	db.query('CREATE TABLE IF NOT EXISTS people (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)');
/* 7  */	let names=['Peter Parker','Clark Kent','Bruce Wayne'];
/* 10 */	for (let name of names) db.query('INSERT INTO people (name) VALUES (?)',[name]);;
/* 14 */	for (let r of db.query('SELECT id, name FROM people')) print(r[0],r[1]);;
/* 18 */	db.close();
