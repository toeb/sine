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

recurse("Types","",Class,0);

print("trying to construct a objcet");

print(" a s",Class.UserDataStruct2);
print(Class.UserDataStruct2.new());

--aObject = Class.UserDataStruct2();
Class.UserDataStruct2.Lol.call();
Class.UserDataStruct2.Value1.get();
Class.UserDataStruct2.Value1.set();
print(Class.UserDataStruct2)
print(Class.UserDataStruct2.Lol)
print(Class.UserDataStruct2.Value1)
print(Class.UserDataStruct2.Value2)

b = aObject.getValue1();
print(b);
print("Ende des scripts");
print("Ende des scripts");
