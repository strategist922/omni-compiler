      program main
      include 'xmp_lib.h'
!$xmp nodes p(*)
      integer procs, id
      integer mask, val, result

      if(xmp_num_nodes().gt.31) then
         print *, 'You have to run this program by less than 32 nodes.'
         call exit(1)
      endif

      procs = xmp_num_nodes()
      id = xmp_node_num()-1
      result = 0
      do i=0, 2**procs-1
         mask = lshift(1, id)
         val = iand(i, mask)
!$xmp reduction(ior: val)
         if(val .ne. i) then
            result = -1
         endif
      enddo

!$xmp reduction(+:result)
!$xmp task on p(1)
      if ( result .eq. 0 ) then
         write(*,*) "PASS"
      else
         write(*,*) "ERROR"
         call exit(1)
      endif

!$xmp end task

      end