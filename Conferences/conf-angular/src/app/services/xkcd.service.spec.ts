import { TestBed } from '@angular/core/testing';

import { XkcdService } from './xkcd.service';

describe('XkcdService', () => {
  let service: XkcdService;

  beforeEach(() => {
    TestBed.configureTestingModule({});
    service = TestBed.inject(XkcdService);
  });

  it('should be created', () => {
    expect(service).toBeTruthy();
  });
});
