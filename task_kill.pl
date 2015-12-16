my $cmd_to_kill=$ARGV[0];
return unless $cmd_to_kill;
for(`tasklist`)
{
	s/\s+$//;
	my($cmd,$pid)=(split)[0,1];
	next unless $cmd eq $cmd_to_kill;
	return system("taskkill   /F /PID  $pid");
}
#wmic也能做 但尚未了解其如何分割显示的内容  
#信息随全 无从下口