-- initializing

function recurse(key, prev, table, depth)
if(depth>10)then return end
if type(table)=="table"then

 for k,v in pairs(table) do
	recurse(k,prev.."."..key,v,depth+1);
 end
else
	print(depth, prev.."."..key, table);

end
end

--asd = function(self,object,...) print(object) end
--asd(1,2,3,45)

recurse("Types","",Types,0);
print("trying to construct a objcet");
print(Types);
print(Types.UserDataStruct2);
print(Types.UserDataStruct2.__new);
print(Types.UserDataStruct2:__new());


print("im westen nichts neues");
